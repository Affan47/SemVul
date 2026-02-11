bmp_555_565(int fd, struct pixel565 *fb, int width, int height, int xres, int yres)
{
	int ret;
	int i, j;
	struct pixel565 *tmp_fb;
	struct pixel555 buff[width];


	for (i = height - 1; i >= 0; i--)
	{
		ret = read(fd, &buff, sizeof(buff));
		if (ret < 0)
		{
			print_error("read");
			return ret;
		}

		for (j = 0; j < width; j++)
		{
			tmp_fb = fb + i * xres + j;

			tmp_fb->red = buff[j].red;
			tmp_fb->green = buff[j].green;
			tmp_fb->green <<= 1;
			tmp_fb->blue = buff[j].blue;
		}
	}

	return 0;
}
