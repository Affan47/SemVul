brasero_job_item_activate (BraseroTaskItem *item,
			   BraseroTaskCtx *ctx,
			   GError **error)
{
	BraseroJob *self;
	BraseroJobClass *klass;
	BraseroJobPrivate *priv;
	BraseroBurnSession *session;
	BraseroBurnResult result = BRASERO_BURN_OK;

	self = BRASERO_JOB (item);
	priv = BRASERO_JOB_PRIVATE (self);
	session = brasero_task_ctx_get_session (ctx);

	g_object_ref (ctx);
	priv->ctx = ctx;

	klass = BRASERO_JOB_GET_CLASS (self);


	if (klass->activate)
		result = klass->activate (self, error);
	else
		BRASERO_BURN_LOG ("no ::activate method %s",
				  G_OBJECT_TYPE_NAME (item));

	if (result != BRASERO_BURN_OK) {
		g_object_unref (ctx);
		priv->ctx = NULL;

		if (result == BRASERO_BURN_NOT_RUNNING)
			result = brasero_job_allow_deactivation (self, session, error);

		return result;
	}

	return BRASERO_BURN_OK;
}
