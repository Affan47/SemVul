bar_pane_keywords_write(PaneKeywordsData *pkd)
{
	GList *list;

	if (!pkd->fd) return;

	list = keyword_list_pull(pkd->keyword_view);

	metadata_write_list(pkd->fd, KEYWORD_KEY, list);

	string_list_free(list);
}
