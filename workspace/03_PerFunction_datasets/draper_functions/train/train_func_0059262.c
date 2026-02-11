brasero_job_item_clock_tick (BraseroTaskItem *item,
			     BraseroTaskCtx *ctx,
			     GError **error)
{
	BraseroJob *self;
	BraseroJobClass *klass;
	BraseroJobPrivate *priv;
	BraseroBurnResult result = BRASERO_BURN_OK;

	self = BRASERO_JOB (item);
	priv = BRASERO_JOB_PRIVATE (self);
	if (!priv->ctx)
		return BRASERO_BURN_OK;

	klass = BRASERO_JOB_GET_CLASS (self);
	if (klass->clock_tick)
		result = klass->clock_tick (self);

	return result;
}
