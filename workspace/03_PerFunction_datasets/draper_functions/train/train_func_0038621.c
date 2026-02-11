print_job_render_image_loader_done(ImageLoader *il, gpointer data)
{
	PrintWindow *pw = data;
	GdkPixbuf *pixbuf;
	gboolean success = TRUE;

	pixbuf = image_loader_get_pixbuf(il);
	if (pixbuf)
		{
		gdouble sw, sh;
		gdouble dw, dh;
		gdouble x, y, w, h;
		gdouble scale;
		gdouble offx, offy;

		sw = (gdouble)gdk_pixbuf_get_width(pixbuf);
		sh = (gdouble)gdk_pixbuf_get_height(pixbuf);

		dw = pw->layout_width - pw->margin_left - pw->margin_right;
		dh = pw->layout_height - pw->margin_top - pw->margin_bottom;

		if (dw / sw < dh / sh)
			{
			w = dw;
			h = dw / sw * sh;
			scale = w / sw;
			}
		else
			{
			h = dh;
			w = dh / sh *sw;
			scale = h / sh;
			}

		if (pw->image_scale >= 5.0)
			{
			w = w * pw->image_scale / 100.0;
			h = h * pw->image_scale / 100.0;
			}

		x = pw->margin_left + (dw / 2) - (w / 2);
		y = pw->margin_top + (dh / 2) - (h / 2);

		offx = offy = 0;

		if (x < 0)
			{
			w += x;
			offx = x;
			x = 0;
			}
		if (x + w >= pw->layout_width) w = pw->layout_width - x;

		if (y < 0)
			{
			h += y;
			offy = y;
			y = 0;
			}
		if (y + h >= pw->layout_height) h = pw->layout_height - y;

		success = (success &&
			   print_job_page_image(pw, pixbuf, x, y, w, h, offx, offy));

		x = x + w / 2;
		y = y + h + PRINT_TEXT_PADDING;

		success = (success &&
			   print_job_text_image(pw, image_loader_get_fd(pw->job_loader)->path, x, y, dw, sw, sh, FALSE));
		}

	image_loader_free(pw->job_loader);
	pw->job_loader = NULL;

	if (pw->job_format == RENDER_FORMAT_PREVIEW)
		{
		print_job_done(pw);
		return;
		}

	success = (success && print_job_page_done(pw));
	if (!success)
		{
		print_job_close(pw, TRUE);
		return;
		}

	pw->job_page++;
	print_job_status(pw);

	if (print_job_render_image(pw))
		{
		if (!print_job_page_new(pw)) print_job_close(pw, TRUE);
		}
	else
		{
		print_job_done(pw);
		}
}
