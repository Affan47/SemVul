wallpaper_copy_done_callback (GHashTable *debuting_files,
			      gboolean success,
			      gpointer data)
{
	GHashTableIter iter;
	gpointer key, value;

	g_hash_table_iter_init (&iter, debuting_files);
	while (g_hash_table_iter_next (&iter, &key, &value)) {
		char *uri;
		uri = g_file_get_uri (G_FILE (key));
		set_uri_as_wallpaper (uri);
		g_free (uri);
		break;
	}
}
