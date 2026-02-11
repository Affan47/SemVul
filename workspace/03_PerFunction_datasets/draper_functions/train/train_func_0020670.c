thumb_loader_setup(ThumbLoader *tl, FileData *fd)
{
	image_loader_free(tl->il);
	tl->il = image_loader_new(fd);
	image_loader_set_priority(tl->il, G_PRIORITY_LOW);


	image_loader_set_requested_size(tl->il, tl->max_w, tl->max_h);

	g_signal_connect(G_OBJECT(tl->il), "error", (GCallback)thumb_loader_error_cb, tl);
	if (tl->func_progress) g_signal_connect(G_OBJECT(tl->il), "percent", (GCallback)thumb_loader_percent_cb, tl);
}
