history_list_free(HistoryData *hd)
{
	GList *work;

	if (!hd) return;

	work = hd->list;
	while (work)
		{
		g_free(work->data);
		work = work->next;
		}

	g_free(hd->key);
	g_free(hd);
}
