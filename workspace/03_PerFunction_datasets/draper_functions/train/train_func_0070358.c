search_progress_notify_cb(gpointer data, gboolean on_server, guint at,
		guint matched, guint total)
{
	AdvancedSearch *search = (AdvancedSearch*) data;

	if (search->search_aborted)
		return FALSE;

	if (on_server || search->on_progress_cb.cb == NULL)
		return TRUE;

	return search->on_progress_cb.cb(search->on_progress_cb.data, at, matched, total);
}
