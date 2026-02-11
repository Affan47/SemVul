gedit_document_input_stream_new (GtkTextBuffer            *buffer,
				 GeditDocumentNewlineType  type,
				 gboolean                  ensure_trailing_newline)
{
	GeditDocumentInputStream *stream;

	g_return_val_if_fail (GTK_IS_TEXT_BUFFER (buffer), NULL);

	stream = g_object_new (GEDIT_TYPE_DOCUMENT_INPUT_STREAM,
			       "buffer", buffer,
			       "newline-type", type,
			       "ensure-trailing-newline", ensure_trailing_newline,
			       NULL);

	return G_INPUT_STREAM (stream);
}
