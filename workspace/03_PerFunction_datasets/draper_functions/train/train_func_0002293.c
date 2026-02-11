starfire_video_update(int scanline, int count)
{
	UINT8 *pix = &starfire_videoram[scanline];
	UINT8 *col = &starfire_colorram[scanline];
	int x, y;


	for (x = 0; x < 256; x += 8)
	{
		for (y = 0; y < count; y++)
			if (scanline_dirty[scanline + y])
			{
				int data = pix[y];
				int color = col[y];

				plot_pixel(tmpbitmap, x + 0, scanline + y, color | ((data >> 2) & 0x20));
				plot_pixel(tmpbitmap, x + 1, scanline + y, color | ((data >> 1) & 0x20));
				plot_pixel(tmpbitmap, x + 2, scanline + y, color | ((data >> 0) & 0x20));
				plot_pixel(tmpbitmap, x + 3, scanline + y, color | ((data << 1) & 0x20));
				plot_pixel(tmpbitmap, x + 4, scanline + y, color | ((data << 2) & 0x20));
				plot_pixel(tmpbitmap, x + 5, scanline + y, color | ((data << 3) & 0x20));
				plot_pixel(tmpbitmap, x + 6, scanline + y, color | ((data << 4) & 0x20));
				plot_pixel(tmpbitmap, x + 7, scanline + y, color | ((data << 5) & 0x20));
			}

		pix += 256;
		col += 256;
	}


	for (y = 0; y < count; y++)
		scanline_dirty[scanline + y] = 0;
}
