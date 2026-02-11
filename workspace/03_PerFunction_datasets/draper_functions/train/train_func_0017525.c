brasero_job_get_speed (BraseroJob *self, guint *speed)
{
	BraseroBurnSession *session;
	BraseroJobPrivate *priv;
	BraseroMedia media;
	guint64 rate;

	BRASERO_JOB_DEBUG (self);

	g_return_val_if_fail (speed != NULL, BRASERO_BURN_ERR);

	priv = BRASERO_JOB_PRIVATE (self);
	session = brasero_task_ctx_get_session (priv->ctx);
	rate = brasero_burn_session_get_rate (session);

	media = brasero_burn_session_get_dest_media (session);
	if (media & BRASERO_MEDIUM_DVD)
		*speed = _round_speed (BRASERO_RATE_TO_SPEED_DVD (rate));
	else if (media & BRASERO_MEDIUM_BD)
		*speed = _round_speed (BRASERO_RATE_TO_SPEED_BD (rate));
	else
		*speed = _round_speed (BRASERO_RATE_TO_SPEED_CD (rate));

	return BRASERO_BURN_OK;
}
