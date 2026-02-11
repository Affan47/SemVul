gbemol_playlist_remove_selected_playlist (GbemolPlaylist *pls)
{
	GtkTreeIter iter;
	gchar *str;
	gboolean oro;
	GtkTreeModel* model;

	if (gtk_tree_selection_get_selected (pls->priv->sel_playlists, &model, &iter))
        {
		gtk_tree_model_get (model, &iter,
				COLUMN_PLAYLISTS_CURRENT, &oro, -1);

		if (!oro)
		{
			gtk_tree_model_get (model, &iter,
					COLUMN_PLAYLISTS_TITLE, &str, -1);
			gbemol_mpd_delete_playlist (pls->priv->mpd, str);
			g_free (str);
		}
		gbemol_playlist_populate_playlists (pls);
	}
}
