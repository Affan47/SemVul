attachment_button_expand_drag_data_get_cb (EAttachmentButton *button,
                                           GdkDragContext *context,
                                           GtkSelectionData *selection,
                                           guint info,
                                           guint time)
{
	EAttachmentView *view;
	EAttachment *attachment;
	gchar *mime_type = NULL;

	attachment = e_attachment_button_get_attachment (button);

	if (attachment != NULL)
		mime_type = e_attachment_dup_mime_type (attachment);

	if (mime_type != NULL) {
		gboolean processed = FALSE;
		GdkAtom atom;
		gchar *atom_name;

		atom = gtk_selection_data_get_target (selection);
		atom_name = gdk_atom_name (atom);

		if (g_strcmp0 (atom_name, mime_type) == 0) {
			CamelMimePart *mime_part;

			mime_part = e_attachment_ref_mime_part (attachment);

			if (mime_part != NULL) {
				CamelDataWrapper *wrapper;
				CamelStream *stream;
				GByteArray *buffer;

				buffer = g_byte_array_new ();
				stream = camel_stream_mem_new ();
				camel_stream_mem_set_byte_array (
					CAMEL_STREAM_MEM (stream),
					buffer);
				wrapper = camel_medium_get_content (
					CAMEL_MEDIUM (mime_part));
				camel_data_wrapper_decode_to_stream_sync (
					wrapper, stream, NULL, NULL);
				g_object_unref (stream);

				gtk_selection_data_set (
					selection, atom, 8,
					buffer->data, buffer->len);
				processed = TRUE;

				g_byte_array_free (buffer, TRUE);

				g_object_unref (mime_part);
			}
		}

		g_free (atom_name);
		g_free (mime_type);

		if (processed)
			return;
	}

	view = e_attachment_button_get_view (button);

	e_attachment_view_drag_data_get (
		view, context, selection, info, time);
}
