pan_cache_sync_date(PanWindow *pw, GList *list)
{
	GList *haystack;
	GList *work;

	haystack = g_list_copy(pw->cache_list);

	work = list;
	while (work)
		{
		FileData *fd;
		GList *needle;

		fd = work->data;
		work = work->next;

		needle = haystack;
		while (needle)
			{
			PanCacheData *pc;

			pc = needle->data;
			if (pc->fd == fd)
				{
				if (pc->cd && pc->cd->have_date && pc->cd->date >= 0)
					{
					fd->date = pc->cd->date;
					}

				haystack = g_list_delete_link(haystack, needle);
				needle = NULL;
				}
			else
				{
				needle = needle->next;
				}
			}
		}

	g_list_free(haystack);
}
