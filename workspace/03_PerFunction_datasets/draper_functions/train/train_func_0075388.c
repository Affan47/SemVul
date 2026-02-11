completion_update(DirPane *dp, const gchar *prefix)
{
	GtkListStore	*cm;
	GFile		*dir;
	GFileEnumerator	*fen;

	if(strcmp(dp->complete.prefix, prefix) == 0)
		return;
	cm = GTK_LIST_STORE(gtk_entry_completion_get_model(dp->complete.compl));
	if(cm == NULL)
		return;

	gtk_list_store_clear(cm);
	dir = g_file_parse_name(prefix);
	if((fen = g_file_enumerate_children(dir, "standard::*", G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, NULL)) != NULL)
	{
		GFileInfo	*child;
		GtkTreeIter	iter;

		while((child = g_file_enumerator_next_file(fen, NULL, NULL)) != NULL)
		{
			if(g_file_info_get_file_type(child) == G_FILE_TYPE_DIRECTORY)
			{
				gchar	buf[4 * PATH_MAX];


				g_snprintf(buf, sizeof buf, "%s%s", prefix, g_file_info_get_name(child));
				gtk_list_store_append(cm, &iter);
				gtk_list_store_set(cm, &iter, 0, buf, -1);
			}
			g_object_unref(G_OBJECT(child));
		}
		g_strlcpy(dp->complete.prefix, prefix, sizeof dp->complete.prefix);
		g_object_unref(fen);
	}
	g_object_unref(G_OBJECT(dir));
}
