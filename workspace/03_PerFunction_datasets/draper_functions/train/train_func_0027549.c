view_bookmarks_check(TEXT_BUFFER_VIEW_REC *view, LINE_REC *line)
{
        BOOKMARK_FIND_REC rec;
	GSList *tmp;

        rec.remove_line = line;
        rec.remove_list = NULL;
	g_hash_table_foreach(view->bookmarks,
			     (GHFunc) bookmark_check_remove, &rec);

	if (rec.remove_list != NULL) {
		for (tmp = rec.remove_list; tmp != NULL; tmp = tmp->next) {
			g_hash_table_remove(view->bookmarks, tmp->data);
			g_free(tmp->data);
		}
		g_slist_free(rec.remove_list);
	}
}
