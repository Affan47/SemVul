brasero_normalize_start (BraseroJob *job,
			 GError **error)
{
	BraseroNormalizePrivate *priv;
	BraseroBurnResult result;

	priv = BRASERO_NORMALIZE_PRIVATE (job);

	priv->album_gain = -1.0;
	priv->album_peak = -1.0;


	brasero_job_get_tracks (job, &priv->tracks);
	if (!priv->tracks)
		return BRASERO_BURN_ERR;

	priv->tracks = g_slist_copy (priv->tracks);

	result = brasero_normalize_set_next_track (job, error);
	if (result == BRASERO_BURN_ERR)
		return BRASERO_BURN_ERR;

	if (result == BRASERO_BURN_OK)
		return BRASERO_BURN_NOT_RUNNING;


	brasero_job_set_current_action (job,
					BRASERO_BURN_ACTION_ANALYSING,
					_("Normalizing tracks"),
					FALSE);

	return BRASERO_BURN_OK;
}
