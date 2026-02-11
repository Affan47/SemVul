brasero_video_disc_name_edited_cb (GtkCellRendererText *cellrenderertext,
				   gchar *path_string,
				   gchar *text,
				   BraseroVideoDisc *self)
{
	BraseroVideoDiscPrivate *priv;
	BraseroTrack *track;
	GtkTreeModel *model;
	GtkTreePath *path;
	GtkTreeIter row;

	priv = BRASERO_VIDEO_DISC_PRIVATE (self);

	priv->editing = 0;

	path = gtk_tree_path_new_from_string (path_string);
	model = gtk_tree_view_get_model (GTK_TREE_VIEW (priv->tree));


	if (!gtk_tree_model_get_iter (model, &row, path)) {
		gtk_tree_path_free (path);
		return;
	}

	track = brasero_video_tree_model_path_to_track (BRASERO_VIDEO_TREE_MODEL (model), path);
	gtk_tree_path_free (path);

	brasero_track_tag_add_string (track, BRASERO_TRACK_STREAM_TITLE_TAG, text);


	brasero_track_changed (track);
}
