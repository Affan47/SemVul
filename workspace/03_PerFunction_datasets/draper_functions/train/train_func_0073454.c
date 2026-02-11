load_icon (gchar *tile_data, guint16 *palette_data)
{
	struct palette_i palette[16];
	int pos, j, i, y, x;

	GdkPixbuf *pixbuf;
	guchar *pixels;
	int rowstride;


	for (i = 0; i < 16; i++) {
		palette[i].r = (palette_data[i] & 0x001F) << 3;
		palette[i].g = (palette_data[i] & 0x03E0) >> 2;
		palette[i].b = (palette_data[i] & 0x7C00) >> 7;
		palette[i].a = (i == 0) ? 0x00 : 0xFF;
	}


	pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8, 32, 32);
	rowstride = gdk_pixbuf_get_rowstride (pixbuf);
	pixels = gdk_pixbuf_get_pixels (pixbuf);


	pos = 0;
	for (j = 0; j < 4; j++) {
		for (i = 0; i < 4; i++) {
			for (y = 0; y < 8; y++) {
				for (x = 0; x < 4; x++) {
					put_pixel (pixels, rowstride, x * 2 + 8 * i,  y + 8 * j, palette[tile_data[pos] & 0x0F]);
					put_pixel (pixels, rowstride, x * 2 + 1 + 8 * i, y + 8 * j, palette[(tile_data[pos] & 0xF0)>>4]);
					pos++;
				}
			}
		}
	}

	return pixbuf;
}
