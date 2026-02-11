_g_bookmark_file_set_uris (GBookmarkFile *bookmark,
			   GList         *uri_list)
{
	GList *scan;

	_g_bookmark_file_clear (bookmark);
	for (scan = uri_list; scan; scan = scan->next)
		_g_bookmark_file_add_uri (bookmark, scan->data);
}
