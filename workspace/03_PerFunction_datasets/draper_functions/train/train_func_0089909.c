thumb_loader_error_cb(ImageLoader *il, gpointer data)
{
	ThumbLoader *tl = data;


	if (image_loader_get_pixbuf(tl->il) != NULL)
		{
		thumb_loader_done_cb(il, data);
		return;
		}

	DEBUG_1("thumb error: %s", tl->fd->path);

	image_loader_free(tl->il);
	tl->il = NULL;

	thumb_loader_set_fallback(tl);

	if (tl->func_error) tl->func_error(tl, tl->data);
}
