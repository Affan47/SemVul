brasero_video_tree_model_iter_n_children (GtkTreeModel *model,
					  GtkTreeIter *iter)
{
	if (!iter) {
		guint num = 0;
		GSList *iter;
		GSList * tracks;
		BraseroVideoTreeModelPrivate *priv;

		priv = BRASERO_VIDEO_TREE_MODEL_PRIVATE (model);


		tracks = brasero_burn_session_get_tracks (BRASERO_BURN_SESSION (priv->session));
		for (iter = tracks; iter; iter = iter->next) {
			BraseroTrackStream *track;

			track = iter->data;
			num ++;

			if (brasero_track_stream_get_gap (track) > 0)
				num ++;
		}

		return num;
	}

	return 0;
}
