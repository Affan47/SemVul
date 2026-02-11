print_job_page_image(PrintWindow *pw, GdkPixbuf *pixbuf,
				     gdouble x, gdouble y, gdouble w, gdouble h,
				     gdouble offx, gdouble offy)
{
	gboolean success = FALSE;

	if (w <= 0.0 || h <= 0.0) return TRUE;

	switch (pw->job_format)
		{
		case RENDER_FORMAT_RGB:
			success = print_job_rgb_page_image(pw, pixbuf, x, y, w, h, offx, offy);
			break;
		case RENDER_FORMAT_PS:
			success = print_job_ps_page_image(pw, pixbuf, x, y, w, h, offx, offy);
			break;
		case RENDER_FORMAT_PREVIEW:
			success = print_job_preview_page_image(pw, pixbuf, x, y, w, h, offx, offy);
			break;
		}

	return success;
}
