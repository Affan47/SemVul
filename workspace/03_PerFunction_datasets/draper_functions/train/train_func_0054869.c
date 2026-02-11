win_wininfo_destroy(WinInfo *wi)
{
	GList *iter;

	for(iter = wi->windows; iter != NULL; iter = g_list_next(iter))
		g_free(iter->data);
	g_list_free(wi->windows);
	g_free(wi);
}
