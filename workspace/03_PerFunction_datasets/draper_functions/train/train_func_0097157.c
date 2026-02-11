attachment_save_read_cb (GInputStream *input_stream,
                         GAsyncResult *result,
                         SaveContext *save_context)
{
	EAttachment *attachment;
	GCancellable *cancellable;
	GOutputStream *output_stream;
	gssize bytes_read;
	GError *error = NULL;

	bytes_read = g_input_stream_read_finish (
		input_stream, result, &error);

	if (attachment_save_check_for_error (save_context, error))
		return;

	if (bytes_read == 0) {
		GSimpleAsyncResult *simple;
		GFile *destination;


		destination = save_context->destination;
		save_context->destination = NULL;

		simple = save_context->simple;
		g_simple_async_result_set_op_res_gpointer (
			simple, destination, (GDestroyNotify) g_object_unref);
		g_simple_async_result_complete (simple);

		attachment_save_context_free (save_context);

		return;
	}

	attachment = save_context->attachment;
	cancellable = attachment->priv->cancellable;
	output_stream = save_context->output_stream;
	save_context->bytes_read = bytes_read;

	attachment_progress_cb (
		g_seekable_tell (G_SEEKABLE (input_stream)),
		save_context->total_num_bytes, attachment);

	g_output_stream_write_async (
		output_stream,
		save_context->buffer,
		save_context->bytes_read,
		G_PRIORITY_DEFAULT, cancellable,
		(GAsyncReadyCallback) attachment_save_write_cb,
		save_context);
}
