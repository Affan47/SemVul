pl3_cp_current_song_changed(GmpcMpdDataModelPlaylist * model2, GtkTreePath * path, GtkTreeIter * iter,
										PlayQueuePlugin * self)
{
	GtkTreeModel *model;
	if (self->priv->pl3_cp_tree == NULL)
		return;
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(self->priv->pl3_cp_tree));
	if (GMPC_IS_MPDDATA_MODEL_PLAYLIST(model))
	{
		if (cfg_get_single_value_as_int_with_default(config, "playlist", "st_cur_song", 0))
		{
			gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(self->priv->pl3_cp_tree), path, NULL, TRUE, 0.5, 0);
		}
	}
}
