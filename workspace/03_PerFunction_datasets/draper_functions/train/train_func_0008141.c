brasero_job_set_current_action (BraseroJob *self,
				BraseroBurnAction action,
				const gchar *string,
				gboolean force)
{
	BraseroJobPrivate *priv;

	BRASERO_JOB_DEBUG (self);

	priv = BRASERO_JOB_PRIVATE (self);
	if (!brasero_job_is_last_active (self))
		return BRASERO_BURN_NOT_RUNNING;

	return brasero_task_ctx_set_current_action (priv->ctx,
						    action,
						    string,
						    force);
}
