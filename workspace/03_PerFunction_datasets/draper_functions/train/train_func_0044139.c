stream_read_async_cb (GObject *obj, GAsyncResult *res, gpointer data)
{
	RBChunkLoader *loader = RB_CHUNK_LOADER (data);
	gssize done;

	done = g_input_stream_read_finish (G_INPUT_STREAM (obj),
					   res,
					   &loader->priv->error);
	if (done == -1) {
		rb_debug ("error reading from stream: %s", loader->priv->error->message);
		g_object_ref (loader);
		loader->priv->callback (loader, NULL, 0, loader->priv->callback_data);
		cleanup (loader);
	} else if (done == 0) {
		rb_debug ("reached end of input stream");
		g_object_ref (loader);
		loader->priv->callback (loader, NULL, 0, loader->priv->callback_data);
		cleanup (loader);
	} else {
		GBytes *bytes;

		bytes = g_bytes_new_take (loader->priv->chunk, done);
		loader->priv->callback (loader, bytes, loader->priv->total, loader->priv->callback_data);
		g_bytes_unref (bytes);

		loader->priv->chunk = g_malloc0 (loader->priv->chunk_size+1);
		g_input_stream_read_async (G_INPUT_STREAM (loader->priv->stream),
					   loader->priv->chunk,
					   loader->priv->chunk_size,
					   G_PRIORITY_DEFAULT,
					   loader->priv->cancel,
					   stream_read_async_cb,
					   loader);
	}
}
