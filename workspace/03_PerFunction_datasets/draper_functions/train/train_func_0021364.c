brasero_task_ctx_get_progress (BraseroTaskCtx *self,
			       gdouble *progress)
{
	BraseroTaskCtxPrivate *priv;
	gdouble track_num = 0;
	gdouble track_nb = 0;
	goffset total = 0;

	priv = BRASERO_TASK_CTX_PRIVATE (self);


	if (priv->action == BRASERO_TASK_ACTION_ERASE) {
		track_num = 1.0;
		track_nb = 0.0;
	}
	else {
		GSList *tracks;

		tracks = brasero_burn_session_get_tracks (priv->session);
		track_num = g_slist_length (tracks);
		track_nb = g_slist_index (tracks, priv->current_track);
	}

	if (priv->progress >= 0.0) {
		if (progress)
			*progress = (gdouble) (track_nb + priv->progress) / (gdouble) track_num;

		return BRASERO_BURN_OK;
	}

	total = 0;
	brasero_task_ctx_get_session_output_size (self, NULL, &total);

	if ((priv->session_bytes + priv->track_bytes) <= 0 || total <= 0) {


		if (priv->timer) {
			if (progress)
				*progress = 0.0;

			return BRASERO_BURN_OK;
		}

		if (progress)
			*progress = -1.0;

		return BRASERO_BURN_NOT_READY;
	}

	if (!progress)
		return BRASERO_BURN_OK;

	*progress = (gdouble) ((gdouble) (priv->track_bytes + priv->session_bytes) / (gdouble)  total);
	return BRASERO_BURN_OK;
}
