brasero_task_ctx_reset (BraseroTaskCtx *self)
{
	BraseroTaskCtxPrivate *priv;
	GSList *tracks;

	priv = BRASERO_TASK_CTX_PRIVATE (self);

	if (priv->tracks) {
		g_slist_foreach (priv->tracks, (GFunc) g_object_unref, NULL);
		g_slist_free (priv->tracks);
		priv->tracks = NULL;
	}

	tracks = brasero_burn_session_get_tracks (priv->session);
	BRASERO_BURN_LOG ("Setting current track (%i tracks)", g_slist_length (tracks));
	if (priv->current_track)
		g_object_unref (priv->current_track);

	if (tracks) {
		priv->current_track = tracks->data;
		g_object_ref (priv->current_track);
	}
	else
		BRASERO_BURN_LOG ("no tracks");

	if (priv->timer) {
		g_timer_destroy (priv->timer);
		priv->timer = NULL;
	}

	priv->dangerous = 0;
	priv->progress = -1.0;
	priv->track_bytes = -1;
	priv->session_bytes = -1;
	priv->written_changed = 0;

	priv->current_elapsed = 0;
	priv->last_written = 0;
	priv->last_elapsed = 0;
	priv->last_progress = 0;

	if (priv->times) {
		g_slist_free (priv->times);
		priv->times = NULL;
	}

	g_signal_emit (self,
		       brasero_task_ctx_signals [PROGRESS_CHANGED_SIGNAL],
		       0);
}
