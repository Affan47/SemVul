rgb8a (XImage *image, guchar *pixels, int rowstride, xlib_colormap *colormap)
{
	int xx, yy;
	int width, height;
	int bpl;
	guint32 mask;
	register guint32 data;
	guint32 remap[256];
	register guint8 *s;
	register guint32 *o;
	guint8 *srow = (guint8 *)image->data, *orow = pixels;

	width = image->width;
	height = image->height;
	bpl = image->bytes_per_line;

	d (printf ("8 bit, with alpha output\n"));

	mask = mask_table[image->depth];

	for (xx = 0; xx < colormap->size; xx++) {
#ifdef LITTLE
		remap[xx] = 0xff000000
			| colormap->colors[xx].blue << 16
			| colormap->colors[xx].green << 8
			| colormap->colors[xx].red;
#else
		remap[xx] = 0xff
			| colormap->colors[xx].red << 24
			| colormap->colors[xx].green << 16
			| colormap->colors[xx].blue << 8;
#endif
	}

	for (yy = 0; yy < height; yy++) {
		s = srow;
		o = (guint32 *) orow;
		for (xx = 0; xx < width; xx ++) {
			data = *s++ & mask;
			*o++ = remap[data];
		}
		srow += bpl;
		orow += rowstride;
	}
}
