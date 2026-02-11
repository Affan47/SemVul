soup_message_io_get_source (SoupMessage *msg, GCancellable *cancellable,
			    SoupMessageSourceFunc callback, gpointer user_data)
{
	SoupMessagePrivate *priv = SOUP_MESSAGE_GET_PRIVATE (msg);
	SoupMessageIOData *io = priv->io_data;
	GSource *base_source, *source;
	SoupMessageSource *message_source;

	if (!io) {
		base_source = g_timeout_source_new (0);
	} else if (io->paused) {
		base_source = NULL;
	} else if (SOUP_MESSAGE_IO_STATE_POLLABLE (io->read_state)) {
		GPollableInputStream *istream;

		if (io->body_istream)
			istream = G_POLLABLE_INPUT_STREAM (io->body_istream);
		else
			istream = G_POLLABLE_INPUT_STREAM (io->istream);
		base_source = g_pollable_input_stream_create_source (istream, cancellable);
	} else if (SOUP_MESSAGE_IO_STATE_POLLABLE (io->write_state)) {
		GPollableOutputStream *ostream;

		if (io->body_ostream)
			ostream = G_POLLABLE_OUTPUT_STREAM (io->body_ostream);
		else
			ostream = G_POLLABLE_OUTPUT_STREAM (io->ostream);
		base_source = g_pollable_output_stream_create_source (ostream, cancellable);
	} else
		base_source = g_timeout_source_new (0);

	source = g_source_new (&message_source_funcs,
			       sizeof (SoupMessageSource));
	g_source_set_name (source, "SoupMessageSource");
	message_source = (SoupMessageSource *)source;
	message_source->msg = g_object_ref (msg);
	message_source->paused = io && io->paused;

	if (base_source) {
		g_source_set_dummy_callback (base_source);
		g_source_add_child_source (source, base_source);
		g_source_unref (base_source);
	}
	g_source_set_callback (source, (GSourceFunc) callback, user_data, NULL);
	return source;
}
