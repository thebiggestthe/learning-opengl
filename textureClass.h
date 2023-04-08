#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "stb_image.h"

#include <iostream>

class Texture
{

public:
	unsigned int ID;
	
	Texture(const char* filepath, GLenum type)
	{
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		// texture wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
		if (data)
		{
			GenerateTextureImage(width, height, data, type);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "failed to load texture" << std::endl;
		}
	}
private:
	void GenerateTextureImage(int width, int height, unsigned char* data, GLenum type)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, type, GL_UNSIGNED_BYTE, data);
	}
};

#endif