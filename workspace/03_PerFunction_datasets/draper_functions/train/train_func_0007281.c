pr_create_anaglyph_dubois(GdkPixbuf *pixbuf, GdkPixbuf *right, gint x, gint y, gint w, gint h)
{
	gint srs, drs;
	guchar *s_pix, *d_pix;
	guchar *sp, *dp;
	guchar *spi, *dpi;
	gint i, j, k;

	srs = gdk_pixbuf_get_rowstride(right);
	s_pix = gdk_pixbuf_get_pixels(right);
	spi = s_pix + (x * COLOR_BYTES);

	drs = gdk_pixbuf_get_rowstride(pixbuf);
	d_pix = gdk_pixbuf_get_pixels(pixbuf);
	dpi =  d_pix + x * COLOR_BYTES;

	for (i = y; i < y + h; i++)
		{
		sp = spi + (i * srs);
		dp = dpi + (i * drs);
		for (j = 0; j < w; j++)
			{
			double res[3];
			for (k = 0; k < 3; k++)
				{
				double *m = pr_dubois_matrix[k];
				res[k] = sp[0] * m[0] + sp[1] * m[1] + sp[2] * m[2] + dp[0] * m[3] + dp[1] * m[4] + dp[2] * m[5];
				if (res[k] < 0.0) res[k] = 0;
				if (res[k] > 255.0) res[k] = 255.0;
				}
			dp[0] = res[0];
			dp[1] = res[1];
			dp[2] = res[2];
			sp += COLOR_BYTES;
			dp += COLOR_BYTES;
			}
		}
}
