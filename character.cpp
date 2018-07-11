
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "character.h"

static int g_frame = 0;

Character::Character()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}
Character::~Character()
{
	free();
}


bool Character::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("unable to load img %s", path.c_str());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

void Character::freeCharacter()
{
	if (this->mTexture != NULL)
	{
		this->mTexture = NULL;
		this->mHeight = 0;
		this->mWidth = 0;
	}
}

void Character::render(int x, int y, SDL_Rect* clip, SDL_Renderer* gRenderer)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}


bool Character::loadCharacter(std::string path, SDL_Renderer* gRenderer)
{
	bool success = true;
	if (!loadFromFile(path, gRenderer))
	{
		printf("could not load character \n");
		success = false;
	}
	else
	{
		Sclip[0].x = 0;
		Sclip[0].y = 0;
		Sclip[0].w = 33;
		Sclip[0].h = 58;

		Sclip[1].x = 33;
		Sclip[1].y = 0;
		Sclip[1].w = 33;
		Sclip[1].h = 58;

		Sclip[2].x = 66;
		Sclip[2].y = 0;
		Sclip[2].w = 33;
		Sclip[2].h = 58;

		Sclip[3].x = 99;
		Sclip[3].y = 0;
		Sclip[3].w = 33;
		Sclip[3].h = 58;
	}
	return success;
}

bool Character::loadCharacter(std::string path, SDL_Renderer* gRenderer, int width_, int height_)
{
	bool success = true;
	if (!loadFromFile(path, gRenderer))
	{
		printf("could not load character \n");
		success = false;
	}
	else
	{
		Sclip[0].x = 0;
		Sclip[0].y = 0;
		Sclip[0].w = width_;
		Sclip[0].h = height_;

		Sclip[1].x = width_;
		Sclip[1].y = 0;
		Sclip[1].w = width_;
		Sclip[1].h = height_;

		Sclip[2].x = width_ * 2;
		Sclip[2].y = 0;
		Sclip[2].w = width_;
		Sclip[2].h = height_;

		Sclip[3].x = width_ * 3;
		Sclip[3].y = 0;
		Sclip[3].w = width_;
		Sclip[3].h = height_;
	}
	return success;
}

void Character::showCharacter(std::string path, SDL_Renderer* gRenderer, bool isDead, int x, int y)
{

	SDL_Rect* currentClip = &Sclip[g_frame / 4];
	render(x, y, currentClip, gRenderer);
	//Update screen

	SDL_Delay(100);
	//Go to next frame
	++g_frame;
	//Cycle animation
	if (g_frame / 4 >= Frames)
	{
		g_frame = 0;
		SDL_Delay(50);
	}
}