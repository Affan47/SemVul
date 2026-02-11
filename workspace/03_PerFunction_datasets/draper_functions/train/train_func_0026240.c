image_sim_fill_data(ImageSimilarityData *sd, GdkPixbuf *pixbuf)
{
	gint w, h;
	gint rs;
	guchar *pix;
	gboolean has_alpha;
	gint p_step;

	guchar *p;
	gint i;
	gint j;
	gint x_inc, y_inc, xy_inc;
	gint xs, ys;

	gboolean x_small = FALSE;
	gboolean y_small = FALSE;

	if (!sd || !pixbuf) return;

	w = gdk_pixbuf_get_width(pixbuf);
	h = gdk_pixbuf_get_height(pixbuf);
	rs = gdk_pixbuf_get_rowstride(pixbuf);
	pix = gdk_pixbuf_get_pixels(pixbuf);
	has_alpha = gdk_pixbuf_get_has_alpha(pixbuf);

	p_step = has_alpha ? 4 : 3;
	x_inc = w / 32;
	y_inc = h / 32;

	if (x_inc < 1)
		{
		x_inc = 1;
		x_small = TRUE;
		}
	if (y_inc < 1)
		{
		y_inc = 1;
		y_small = TRUE;
		}

	xy_inc = x_inc * y_inc;

	j = 0;

	for (ys = 0; ys < 32; ys++)
		{
		if (y_small) j = (gdouble)h / 32 * ys;

		i = 0;

		for (xs = 0; xs < 32; xs++)
			{
			gint x, y;
			gint r, g, b;
			gint t;
			guchar *xpos;

			if (x_small) i = (gdouble)w / 32 * xs;

			r = g = b = 0;
			xpos = pix + (i * p_step);

			for (y = j; y < j + y_inc; y++)
				{
				p = xpos + (y * rs);
				for (x = i; x < i + x_inc; x++)
					{
					r += *p; p++;
					g += *p; p++;
					b += *p; p++;
					if (has_alpha) p++;
					}
				}

			r /= xy_inc;
			g /= xy_inc;
			b /= xy_inc;

			t = ys * 32 + xs;
			sd->avg_r[t] = r;
			sd->avg_g[t] = g;
			sd->avg_b[t] = b;

			i += x_inc;
			}

		j += y_inc;
		}

	sd->filled = TRUE;
}
