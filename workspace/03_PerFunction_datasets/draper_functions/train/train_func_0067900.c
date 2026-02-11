GL_RecursiveGenerateAlphaMipmaps (byte *data, int width, int height, int depth)
{
	int			ret;
	int			x, y;
	int			newwidth, newheight;
	int			upper_left_alpha;
	qboolean	uniform = true;
	byte		*mipmap, *scan, *scan2, *out;

	if (width == 1 && height == 1)
		return depth;

	newwidth = width;
	if (newwidth > 1)
		newwidth /= 2;
	newheight = height;
	if (newheight > 1)
		newheight /= 2;

	mipmap = malloc (newwidth*newheight*4);

	for (y = 0; (y+1) < height; y += 2)
	{
		for (x = 0; (x+1) < width; x += 2)
		{
			scan = data + (y*width+x)*4;
			scan2 = data + ((y+1)*width+x)*4;
			out = mipmap + ((y/2)*(width/2)+(x/2))*4;
			out[0] = (scan[0]+scan[4]+scan2[0]+scan2[4])/4;
			out[1] = (scan[1]+scan[5]+scan2[1]+scan2[5])/4;
			out[2] = (scan[2]+scan[6]+scan2[2]+scan2[6])/4;
			out[3] = (scan[3]+scan[7]+scan2[3]+scan2[7])/4;
			if (x == 0 && y == 0)
				upper_left_alpha = out[3];
			else if ((upper_left_alpha > ALPHATEST_THRESHOLD) != (out[3] > ALPHATEST_THRESHOLD))
				uniform = false;
		}
	}

	if (uniform)
	{
		free (mipmap);
		return depth;
	}

	ret = GL_RecursiveGenerateAlphaMipmaps (mipmap, newwidth, newheight, depth+1);

	qglTexImage2D (GL_TEXTURE_2D, depth+1, gl_tex_alpha_format, newwidth, newheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mipmap);

	free (mipmap);
	return ret;
}
