fz_unmultiply_pixmap(fz_context *ctx, fz_pixmap *pix)
{
	unsigned char *s = pix->samples;
	int a, inva;
	int k, x, y;

	for (y = 0; y < pix->h; y++)
	{
		for (x = 0; x < pix->w; x++)
		{
			a = s[pix->n - 1];
			inva = a ? 255 * 256 / a : 0;
			for (k = 0; k < pix->n - 1; k++)
				s[k] = (s[k] * inva) >> 8;
			s += pix->n;
		}
	}
}
