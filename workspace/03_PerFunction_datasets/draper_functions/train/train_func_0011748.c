gdata_upload_stream_write (GOutputStream *stream, const void *buffer, gsize count, GCancellable *cancellable, GError **error_out)
{
	GDataUploadStreamPrivate *priv = GDATA_UPLOAD_STREAM (stream)->priv;
	gssize length_written = -1;
	gulong cancelled_signal = 0, global_cancelled_signal = 0;
	gboolean cancelled = FALSE;
	gsize old_total_network_bytes_written;
	CancelledData data;
	GError *error = NULL;


	data.upload_stream = GDATA_UPLOAD_STREAM (stream);
	data.cancelled = &cancelled;

	global_cancelled_signal = g_cancellable_connect (priv->cancellable, (GCallback) write_cancelled_cb, &data, NULL);

	if (cancellable != NULL)
		cancelled_signal = g_cancellable_connect (cancellable, (GCallback) write_cancelled_cb, &data, NULL);


	g_mutex_lock (&(priv->write_mutex));

	if (cancelled == TRUE) {
		g_assert (g_cancellable_set_error_if_cancelled (cancellable, &error) == TRUE ||
		          g_cancellable_set_error_if_cancelled (priv->cancellable, &error) == TRUE);
		g_mutex_unlock (&(priv->write_mutex));

		length_written = -1;
		goto done;
	}

	g_mutex_unlock (&(priv->write_mutex));


	old_total_network_bytes_written = priv->total_network_bytes_written;
	priv->message_bytes_outstanding += count;


	if (priv->network_thread != NULL) {

		gdata_buffer_push_data (priv->buffer, buffer, count);
		goto write;
	}


	gdata_buffer_push_data (priv->buffer, buffer, count);


	create_network_thread (GDATA_UPLOAD_STREAM (stream), &error);
	if (priv->network_thread == NULL) {
		length_written = -1;
		goto done;
	}

write:
	g_mutex_lock (&(priv->write_mutex));


	while (priv->total_network_bytes_written - old_total_network_bytes_written < count && cancelled == FALSE && priv->state != STATE_FINISHED) {
		g_cond_wait (&(priv->write_cond), &(priv->write_mutex));
	}
	length_written = MIN (count, priv->total_network_bytes_written - old_total_network_bytes_written);


	if (cancelled == TRUE && length_written < 1) {

		g_assert (g_cancellable_set_error_if_cancelled (cancellable, &error) == TRUE ||
		          g_cancellable_set_error_if_cancelled (priv->cancellable, &error) == TRUE);
		length_written = -1;
	} else if (priv->state == STATE_FINISHED && (length_written < 0 || (gsize) length_written < count)) {

		g_set_error (&error, G_IO_ERROR, G_IO_ERROR_FAILED, _("Error received from server after uploading a resumable upload chunk."));
		length_written = -1;
	}

	g_mutex_unlock (&(priv->write_mutex));

done:


	if (cancelled_signal != 0)
		g_cancellable_disconnect (cancellable, cancelled_signal);
	if (global_cancelled_signal != 0)
		g_cancellable_disconnect (priv->cancellable, global_cancelled_signal);

	g_assert (error != NULL || length_written > 0);

	if (error != NULL) {
		g_propagate_error (error_out, error);
	}

	return length_written;
}
