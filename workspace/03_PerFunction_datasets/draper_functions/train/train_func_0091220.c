rb_async_copy_start (RBAsyncCopy *copy,
		     const char *src,
		     const char *dest,
		     RBAsyncCopyCallback callback,
		     gpointer user_data,
		     GDestroyNotify destroy_data)
{
	g_assert (copy->priv->src == NULL);

	copy->priv->cancel = g_cancellable_new ();

	copy->priv->callback = callback;
	copy->priv->callback_data = user_data;
	copy->priv->destroy_data = destroy_data;

	copy->priv->src = g_file_new_for_commandline_arg (src);
	copy->priv->dest = g_file_new_for_commandline_arg (dest);

	g_file_copy_async (copy->priv->src,
			   copy->priv->dest,
			   G_FILE_COPY_NONE,
			   G_PRIORITY_DEFAULT,
			   copy->priv->cancel,
			   progress_cb,
			   copy,
			   copy_cb,
			   copy);
}
