summaryview_quicksearch_recursive_progress(gpointer data, guint at, guint matched, guint total)
{
	QuickSearch *search = (QuickSearch*) data;
	gint interval = quicksearch_is_fast(search) ? 5000 : 100;

	statusbar_progress_all(at, total, interval);
	if (at % interval == 0)
		GTK_EVENTS_FLUSH();

	if (matched > 0)
		return FALSE;

	return TRUE;
}
