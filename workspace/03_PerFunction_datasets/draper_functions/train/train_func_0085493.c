pl3_current_playlist_browser_paste_after_songs(GtkTreeView * tree, GList * paste_list,
														   PlayQueuePlugin * self)
{

	GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(self->priv->pl3_cp_tree));

	int seen = 0;


	if (gtk_tree_selection_count_selected_rows(selection) > 0)
	{
		GList *list = NULL, *llist = NULL;
		GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(self->priv->pl3_cp_tree));


		list = gtk_tree_selection_get_selected_rows(selection, &model);

		llist = g_list_last(list);

		if (llist)
		{
			GtkTreeIter iter;
			gtk_tree_model_get_iter(model, &iter, (GtkTreePath *) llist->data);

			{
				int id;
				char *path = NULL;
				int length = mpd_playlist_get_playlist_length(connection);
				GList *liter = g_list_first(paste_list);
				gtk_tree_model_get(model, &iter, MPDDATA_MODEL_COL_SONG_POS, &id, -1);
				while (liter)
				{
					int song_id;
					path = liter->data;
					song_id = mpd_playlist_add_get_id(connection, path);
					if (song_id == -1 && !seen)
					{
						playlist3_show_error_message(_("Your mpd has a broken 'addid', pasting will fail."),
													 ERROR_WARNING);
						seen = 1;
					}
					mpd_playlist_move_pos(connection, length, id);
					length++;
					liter = g_list_next(liter);
				}
			}
		}

		g_list_foreach(list, (GFunc) gtk_tree_path_free, NULL);
		g_list_free(list);
	} else
	{
		GList *liter = g_list_first(paste_list);;
		while (liter)
		{
			char *path = liter->data;
			int song_id = mpd_playlist_add_get_id(connection, path);
			if (song_id == -1 && !seen)
			{
				playlist3_show_error_message(_("Your mpd has a broken 'addid', pasting will fail."), ERROR_WARNING);
				seen = 1;
			}
			liter = g_list_next(liter);
		}

	}
	gtk_tree_selection_unselect_all(selection);
}
