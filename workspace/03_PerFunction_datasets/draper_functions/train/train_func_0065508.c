brasero_transcode_buffer_handler (GstPad *pad,
                                  GstPadProbeInfo *info,
                                  gpointer user_data)
{
	BraseroTranscodePrivate *priv;
	BraseroTranscode *self = user_data;
	GstBuffer *buffer = GST_PAD_PROBE_INFO_BUFFER (info);
	GstPad *peer;
	gint64 size;

	priv = BRASERO_TRANSCODE_PRIVATE (self);

	size = gst_buffer_get_size (buffer);

	if (priv->segment_start <= 0 && priv->segment_end <= 0)
		return GST_PAD_PROBE_OK;


	if (priv->size > priv->segment_end) {
		priv->size += size;
		return GST_PAD_PROBE_DROP;
	}

	if (priv->size + size > priv->segment_end) {
		GstBuffer *new_buffer;
		int data_size;


		data_size = priv->segment_end - priv->size;
		new_buffer = gst_buffer_copy_region (buffer, GST_BUFFER_COPY_METADATA, 0, data_size);


		peer = gst_pad_get_peer (pad);
		gst_pad_push (peer, new_buffer);

		priv->size += size - data_size;


		gst_pad_push_event (peer, gst_event_new_eos ());
		gst_object_unref (peer);
		return GST_PAD_PROBE_DROP;
	}


	if (priv->size < priv->segment_start) {
		GstBuffer *new_buffer;
		gint data_size;


		if (priv->size + size < priv->segment_start) {
			priv->size += size;
			return GST_PAD_PROBE_DROP;
		}


		data_size = priv->size + size - priv->segment_start;
		new_buffer = gst_buffer_copy_region (buffer, GST_BUFFER_COPY_METADATA, size - data_size, data_size);

		GST_BUFFER_TIMESTAMP (new_buffer) = GST_BUFFER_TIMESTAMP (buffer) + data_size;


		priv->size += size - data_size;


		peer = gst_pad_get_peer (pad);
		gst_pad_push (peer, new_buffer);
		gst_object_unref (peer);

		return GST_PAD_PROBE_DROP;
	}

	priv->size += size;
	priv->pos += size;

	return GST_PAD_PROBE_OK;
}
