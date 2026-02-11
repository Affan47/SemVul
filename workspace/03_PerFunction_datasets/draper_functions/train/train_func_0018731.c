pixbuf_renderer_set_stereo_data(PixbufRenderer *pr, StereoPixbufData stereo_data)
{
	g_return_if_fail(IS_PIXBUF_RENDERER(pr));

	pr->stereo_data = stereo_data;

	if (pr->stereo_mode & PR_STEREO_TEMP_DISABLE)
		{
		gint disable = !pr->pixbuf || ! pr->stereo_data;
		pr_stereo_temp_disable(pr, disable);
		}
	pr_pixbuf_size_sync(pr);
	pr_zoom_sync(pr, pr->zoom, PR_ZOOM_FORCE, 0, 0);
}
