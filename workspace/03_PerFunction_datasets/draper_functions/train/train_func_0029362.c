brasero_video_tree_model_path_to_track (BraseroVideoTreeModel *self,
				        GtkTreePath *path)
{
	BraseroVideoTreeModelPrivate *priv;
	const gint *indices;
	GSList *tracks;
	guint depth;
	gint index;

	priv = BRASERO_VIDEO_TREE_MODEL_PRIVATE (self);

	indices = gtk_tree_path_get_indices (path);
	depth = gtk_tree_path_get_depth (path);


	if (depth > 2)
		return NULL;


	tracks = brasero_burn_session_get_tracks (BRASERO_BURN_SESSION (priv->session));
	index = indices [0];
	for (; tracks; tracks = tracks->next) {
		BraseroTrackStream *track;

		track = tracks->data;
		if (index <= 0)
			return BRASERO_TRACK (track);

		index --;

		if (brasero_track_stream_get_gap (track) > 0) {
			if (index <= 0)
				return BRASERO_TRACK (track);

				index --;
		}
	}

	return NULL;
}
