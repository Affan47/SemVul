attachment_save_got_output_stream (SaveContext *save_context)
{
	GCancellable *cancellable;
	GInputStream *input_stream;
	CamelDataWrapper *wrapper;
	CamelMimePart *mime_part;
	CamelStream *stream;
	EAttachment *attachment;
	GByteArray *buffer;

	attachment = save_context->attachment;
	cancellable = attachment->priv->cancellable;
	mime_part = e_attachment_ref_mime_part (attachment);


	buffer = g_byte_array_new ();
	stream = camel_stream_mem_new ();
	camel_stream_mem_set_byte_array (CAMEL_STREAM_MEM (stream), buffer);
	wrapper = camel_medium_get_content (CAMEL_MEDIUM (mime_part));
	camel_data_wrapper_decode_to_stream_sync (wrapper, stream, NULL, NULL);
	g_object_unref (stream);


	input_stream = g_memory_input_stream_new ();
	if (buffer->len > 0)
		g_memory_input_stream_add_data (
			G_MEMORY_INPUT_STREAM (input_stream),
			buffer->data, (gssize) buffer->len,
			(GDestroyNotify) g_free);
	save_context->input_stream = input_stream;
	save_context->total_num_bytes = (goffset) buffer->len;
	g_byte_array_free (buffer, FALSE);

	g_input_stream_read_async (
		input_stream,
		save_context->buffer,
		sizeof (save_context->buffer),
		G_PRIORITY_DEFAULT, cancellable,
		(GAsyncReadyCallback) attachment_save_read_cb,
		save_context);

	g_clear_object (&mime_part);
}
