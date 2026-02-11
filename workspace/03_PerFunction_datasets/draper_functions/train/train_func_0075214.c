brasero_task_finished (BraseroTaskCtx *ctx,
		       BraseroBurnResult retval,
		       GError *error)
{
	BraseroTask *self;
	BraseroTaskPrivate *priv;

	self = BRASERO_TASK (ctx);
	priv = BRASERO_TASK_PRIVATE (self);


	if (!brasero_task_is_running (self))
		return;

	if (retval == BRASERO_BURN_RETRY) {
		BraseroTaskItem *item;
		GError *error_item = NULL;


		item = priv->leader;
		while (brasero_task_item_previous (item))
			item = brasero_task_item_previous (item);

		if (brasero_task_item_start (item, &error_item) != BRASERO_BURN_OK)
			brasero_task_stop (self, BRASERO_BURN_ERR, error_item);

		return;
	}

	brasero_task_stop (self, retval, error);
}
