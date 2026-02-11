dmap_gst_input_stream_read (GInputStream * stream,
			    void *buffer,
			    gsize count,
			    GCancellable * cancellable, GError ** error)
{
	int i;
	DMAPGstInputStream *gst_stream = DMAP_GST_INPUT_STREAM (stream);
	gint64 end_time;

	end_time = end_time = g_get_monotonic_time () + QUEUE_POP_WAIT_SECONDS * G_TIME_SPAN_SECOND;

	g_mutex_lock (&gst_stream->priv->buffer_mutex);

	gst_stream->priv->read_request = count;
	if (g_queue_get_length (gst_stream->priv->buffer) < count
	    && !g_cond_wait_until (&gst_stream->priv->buffer_read_ready,
	                           &gst_stream->priv->buffer_mutex, end_time)) {


		g_warning ("Timeout waiting for converted data");


		count = min (count, g_queue_get_length (gst_stream->priv->buffer));
	}

	for (i = 0; i < count; i++) {
		((guint8 *) buffer)[i] =
			GPOINTER_TO_INT (g_queue_pop_head (gst_stream->priv->buffer));
	}

	if (gst_stream->priv->write_request > count)
		gst_stream->priv->write_request -= count;
	else
		gst_stream->priv->write_request = 0;

	if (gst_stream->priv->write_request <= 0) {
		g_cond_signal (&gst_stream->priv->buffer_write_ready);
	}

	g_mutex_unlock (&gst_stream->priv->buffer_mutex);

	return count;
}
