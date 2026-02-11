progress_cb (goffset current_num_bytes, goffset total_bytes, gpointer data)
{
	RBAsyncCopy *copy = RB_ASYNC_COPY (data);

	if (copy->priv->progress)
		copy->priv->progress (copy, current_num_bytes, total_bytes, copy->priv->progress_data);
}
