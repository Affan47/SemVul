slideshow_unref (SlideShow *show)
{
	GList *list;
	GSList *slist;
	FileSize *size;

	show->ref_count--;
	if (show->ref_count > 0)
		return;

	for (list = show->slides->head; list != NULL; list = list->next) {
		Slide *slide = list->data;

		for (slist = slide->file1; slist != NULL; slist = slist->next) {
			size = slist->data;
			g_free (size->file);
			g_free (size);
		}
		g_slist_free (slide->file1);

		for (slist = slide->file2; slist != NULL; slist = slist->next) {
			size = slist->data;
			g_free (size->file);
			g_free (size);
		}
		g_slist_free (slide->file2);

		g_free (slide);
	}

	g_queue_free (show->slides);

	g_list_foreach (show->stack->head, (GFunc) g_free, NULL);
	g_queue_free (show->stack);

	g_free (show);
}
