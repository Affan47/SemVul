dmap_gst_input_stream_new_buffer_cb (GstElement * element,
				     DMAPGstInputStream * stream)
{
	gsize i;
	guint8 *ptr;
	gint64 end_time;
	GstSample *sample = NULL;
	GstBuffer *buffer = NULL;
	GstMemory *memory = NULL;
	GstMapInfo info;


	g_mutex_lock (&stream->priv->buffer_mutex);

	if (stream->priv->buffer_closed) {
		g_warning ("Buffer is closed, but unread data remains");
		goto _return;
	}

	end_time = g_get_monotonic_time () + QUEUE_PUSH_WAIT_SECONDS * G_TIME_SPAN_SECOND;

	sample = gst_app_sink_pull_sample (GST_APP_SINK (element));
	if (NULL == sample) {
		g_warning ("Error getting GStreamer sample");
		goto _return;
	}

	buffer = gst_sample_get_buffer (sample);
	if (NULL == buffer) {
		g_warning ("Error getting GStreamer buffer");
		goto _return;
	}

	memory = gst_buffer_get_memory (buffer, 0);
	if (NULL == memory) {
		g_warning ("Error getting GStreamer memory");
		goto _return;
	}

	if (gst_memory_map (memory, &info, GST_MAP_READ) == FALSE) {
		g_warning ("Error mapping GStreamer memory");
		goto _return;
	}


	if (g_queue_get_length (stream->priv->buffer) + info.size > DECODED_BUFFER_SIZE) {
		stream->priv->write_request = info.size;
		if (!g_cond_wait_until (&stream->priv->buffer_write_ready,
		                        &stream->priv->buffer_mutex, end_time)) {
			g_warning ("Timeout waiting for buffer to empty; will drop");
		}

		if (stream->priv->buffer_closed) {
			g_warning ("Unread data");
			goto _return;
		}
	} else {
		stream->priv->write_request = 0;
	}

	if (g_queue_get_length (stream->priv->buffer) + info.size <= DECODED_BUFFER_SIZE) {
		ptr = info.data;

		for (i = 0; i < info.size; i++) {
			g_queue_push_tail (stream->priv->buffer,
					   GINT_TO_POINTER ((gint) * ptr++));
		}
	}

	if (g_queue_get_length (stream->priv->buffer) >= stream->priv->read_request) {
		stream->priv->read_request = 0;
		g_cond_signal (&stream->priv->buffer_read_ready);
	}

      _return:
	if (NULL != memory) {
		gst_memory_unmap (memory, &info);
		gst_memory_unref (memory);
	}

	if (NULL != sample) {
		gst_sample_unref (sample);
	}

	g_mutex_unlock (&stream->priv->buffer_mutex);
}
