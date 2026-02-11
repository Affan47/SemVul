pl3_file_browser_add_to_playlist(GtkWidget * menu, gpointer cb_data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(pl3_fb_store2);
	GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(pl3_fb_tree));
	gchar *data = g_object_get_data(G_OBJECT(menu), "playlist");
	GList *iter, *list = gtk_tree_selection_get_selected_rows(selection, &model);
	if (list)
	{
		iter = g_list_first(list);
		do
		{
			GtkTreeIter giter;
			if (gtk_tree_model_get_iter(model, &giter, (GtkTreePath *) iter->data))
			{
				gchar *file = NULL;
				int type = 0;
				gtk_tree_model_get(model, &giter, MPDDATA_MODEL_COL_PATH, &file, MPDDATA_MODEL_ROW_TYPE, &type, -1);
				if (type == MPD_DATA_TYPE_SONG)
				{
					mpd_database_playlist_list_add(connection, data, file);
				} else if (type == MPD_DATA_TYPE_DIRECTORY)
				{
					MpdData *data2 = mpd_database_get_directory_recursive(connection, file);
					for (; data2; data2 = mpd_data_get_next(data2))
					{
						if (data2->type == MPD_DATA_TYPE_SONG)
						{
							mpd_database_playlist_list_add(connection, data, data2->song->file);
						}
					}
				}
				g_free(file);
			}
		} while ((iter = g_list_next(iter)));

		g_list_foreach(list, (GFunc) gtk_tree_path_free, NULL);
		g_list_free(list);
	}
}
