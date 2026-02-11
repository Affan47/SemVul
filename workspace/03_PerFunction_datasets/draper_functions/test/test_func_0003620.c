brasero_async_task_manager_foreach_active (BraseroAsyncTaskManager *self,
					   BraseroAsyncFindTask func,
					   gpointer user_data)
{
	GSList *iter;
	BraseroAsyncTaskCtx *ctx;
	gboolean result = FALSE;

	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (func != NULL, FALSE);

	g_mutex_lock (self->priv->lock);
	for (iter = self->priv->active_tasks; iter; iter = iter->next) {
		ctx = iter->data;
		if (func (self, ctx->data, user_data))
			result = TRUE;
	}
	g_mutex_unlock (self->priv->lock);

	return result;
}
