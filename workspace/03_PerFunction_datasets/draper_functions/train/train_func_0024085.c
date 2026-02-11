gm_world_logs_dialog_fill(GmWorld *world, GtkTreeView *view,
		GtkTreeModel *model, GError **err) {
	gint res = 0;
	gchar *path, *tmp, *tmp2;
	gchar const *fname;
	GDir *dir;
	GtkTreeIter iter;
	FILE *f;
	long fsize;


	path = g_strdup_printf("%s/logs/", gm_world_path(world));
	dir = g_dir_open(path, 0, err);

	if (dir) {
		while ((fname = g_dir_read_name(dir)) != NULL) {
			++res;
			tmp = g_strconcat(path, fname, NULL);
			f = fopen(tmp, "r");

			if (f) {
				fseek(f, 0, SEEK_END);
				fsize = ftell(f);
				fclose(f);
				g_free(tmp);

				tmp = gnome_vfs_format_file_size_for_display(fsize);
				tmp2 = g_strconcat(fname, " (", tmp, ")", NULL);

				gtk_list_store_prepend(GTK_LIST_STORE(model), &iter);
				gtk_list_store_set(GTK_LIST_STORE(model), &iter, 0, fname, 1,
						tmp2, -1);
				g_free(tmp2);
			}

			g_free(tmp);
		}

		g_dir_close(dir);
		g_free(path);
    	return res;
	} else {
		g_free(path);
		return -1;
	}
}
