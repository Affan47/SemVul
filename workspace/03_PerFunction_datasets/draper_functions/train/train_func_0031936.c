cd_library_popup_replace_clicked (GtkWidget *widget, gpointer data)
{

	GtkTreeModel 		*model;
	GtkTreeIter 		iter;
	GList			*list;
	gchar			*path;
	GimmixFileType		type;

	model = gtk_tree_view_get_model (GTK_TREE_VIEW (library_treeview));
	list = gtk_tree_selection_get_selected_rows (library_selection, &model);

	gimmix_current_playlist_clear();
	mpd_status_update (gmo);

	if (gtk_tree_selection_count_selected_rows (library_selection) == 1)
	{
		gtk_tree_model_get_iter (model, &iter, list->data);
		gtk_tree_model_get (model, &iter, 2, &path, 3, &type, -1);

		if (type == GIMMIX_DIR)
		{
			mpd_playlist_queue_add (gmo, path);
		}
		else if (type == SONG)
		{
			mpd_playlist_add (gmo, path);
		}

		g_free (path);
	}
	else
	while (list != NULL)
	{
		gtk_tree_model_get_iter (model, &iter, list->data);
		gtk_tree_model_get (model, &iter, 2, &path, 3, &type, -1);


		if (type == GIMMIX_DIR)
		{
			mpd_playlist_queue_add (gmo, path);
			g_free (path);
		}

		if (type == SONG)
		{
			mpd_playlist_queue_add (gmo, path);
			g_free (path);
		}

		list = g_list_next (list);
	}

	mpd_playlist_queue_commit (gmo);

	if (gimmix_config_get_bool("play_on_add"))
	{
		gimmix_play(gmo);
	}
	mpd_status_update (gmo);


	g_list_foreach (list, (GFunc)gtk_tree_path_free, NULL);
	g_list_free (list);

	return;
}
