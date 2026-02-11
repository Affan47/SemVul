thumb_loader_done_delay_cb(gpointer data)
{
	ThumbLoader *tl = data;

	tl->idle_done_id = 0;

	if (tl->func_done) tl->func_done(tl, tl->data);

	return FALSE;
}
