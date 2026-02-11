brasero_job_get_bus_target_lun (BraseroJob *self, gchar **BTL)
{
	BraseroBurnSession *session;
	BraseroJobPrivate *priv;
	BraseroDrive *drive;

	BRASERO_JOB_DEBUG (self);

	g_return_val_if_fail (BTL != NULL, BRASERO_BURN_ERR);

	priv = BRASERO_JOB_PRIVATE (self);
	session = brasero_task_ctx_get_session (priv->ctx);

	drive = brasero_burn_session_get_burner (session);
	*BTL = brasero_drive_get_bus_target_lun_string (drive);

	return BRASERO_BURN_OK;
}
