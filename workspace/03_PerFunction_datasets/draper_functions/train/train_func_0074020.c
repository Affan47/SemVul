brasero_local_track_clock_tick (BraseroJob *job)
{
	BraseroLocalTrackPrivate *priv;
	goffset written = 0;
	goffset total = 0;

	priv = BRASERO_LOCAL_TRACK_PRIVATE (job);

	if (!priv->xfer_ctx)
		return BRASERO_BURN_OK;

	brasero_job_start_progress (job, FALSE);

	brasero_xfer_get_progress (priv->xfer_ctx,
				   &written,
				   &total);
	brasero_job_set_progress (job, (gdouble) written / (gdouble) total);

	return BRASERO_BURN_OK;
}
