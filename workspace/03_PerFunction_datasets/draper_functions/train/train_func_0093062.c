fz_invert_pixmap_rect(fz_pixmap *image, fz_bbox rect)
{
	unsigned char *p;
	int x, y, n;

	int x0 = fz_clampi(rect.x0 - image->x, 0, image->w - 1);
	int x1 = fz_clampi(rect.x1 - image->x, 0, image->w - 1);
	int y0 = fz_clampi(rect.y0 - image->y, 0, image->h - 1);
	int y1 = fz_clampi(rect.y1 - image->y, 0, image->h - 1);

	for (y = y0; y < y1; y++)
	{
		p = image->samples + (unsigned int)((y * image->w + x0) * image->n);
		for (x = x0; x < x1; x++)
		{
			for (n = image->n; n > 0; n--, p++)
				*p = 255 - *p;
		}
	}
}
