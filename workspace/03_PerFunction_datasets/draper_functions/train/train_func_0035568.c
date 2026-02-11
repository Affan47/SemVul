missile_blit_w (offs_t offset)
{
	int x, y;
	int bottom;
	int color;


	y = (offset >> 8) - 25;
	x = offset & 0xff;
	if( y < 231 - 32)
		bottom = 1;
	else
		bottom = 0;


	if (flip_screen)
	{
		y = tmpbitmap->height - 1 - y;
	}

	color = (missile_videoram[offset] >> 5);

	if (bottom) color &= 0x06;

	plot_pixel(tmpbitmap, x, y, Machine->pens[color]);
}
