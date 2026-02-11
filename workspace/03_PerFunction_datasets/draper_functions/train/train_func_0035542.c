nemo_bookmark_list_set_window_geometry (NemoBookmarkList *bookmarks,
					    const char           *geometry)
{
	g_return_if_fail (NEMO_IS_BOOKMARK_LIST (bookmarks));
	g_return_if_fail (geometry != NULL);

	g_free (window_geometry);
	window_geometry = g_strdup (geometry);

	nemo_bookmark_list_save_file (bookmarks);
}
