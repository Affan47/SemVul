data_capture_convert (GConverter *converter,
                      gconstpointer inbuf,
                      gsize inbuf_size,
                      gpointer outbuf,
                      gsize outbuf_size,
                      GConverterFlags flags,
                      gsize *bytes_read,
                      gsize *bytes_written,
                      GError **error)
{
	EDataCapture *data_capture;
	GConverterResult result;

	data_capture = E_DATA_CAPTURE (converter);


	if (outbuf_size < inbuf_size) {
		g_set_error_literal (
			error, G_IO_ERROR,
			G_IO_ERROR_NO_SPACE,
			"EDataCapture needs more space");
		return G_CONVERTER_ERROR;
	}

	memcpy (outbuf, inbuf, inbuf_size);
	*bytes_read = *bytes_written = inbuf_size;

	g_mutex_lock (&data_capture->priv->byte_array_lock);

	g_byte_array_append (
		data_capture->priv->byte_array, inbuf, inbuf_size);

	if ((flags & G_CONVERTER_INPUT_AT_END) != 0) {
		GSource *idle_source;
		GMainContext *main_context;
		SignalClosure *signal_closure;

		signal_closure = g_slice_new0 (SignalClosure);
		g_weak_ref_set (&signal_closure->data_capture, data_capture);
		signal_closure->data = g_bytes_new (
			data_capture->priv->byte_array->data,
			data_capture->priv->byte_array->len);

		main_context = e_data_capture_ref_main_context (data_capture);

		idle_source = g_idle_source_new ();
		g_source_set_callback (
			idle_source,
			data_capture_emit_finished_idle_cb,
			signal_closure,
			(GDestroyNotify) signal_closure_free);
		g_source_set_priority (idle_source, G_PRIORITY_HIGH_IDLE);
		g_source_attach (idle_source, main_context);
		g_source_unref (idle_source);

		g_main_context_unref (main_context);
	}

	g_mutex_unlock (&data_capture->priv->byte_array_lock);

	if ((flags & G_CONVERTER_INPUT_AT_END) != 0)
		result = G_CONVERTER_FINISHED;
	else if ((flags & G_CONVERTER_FLUSH) != 0)
		result = G_CONVERTER_FLUSHED;
	else
		result = G_CONVERTER_CONVERTED;

	return result;
}
