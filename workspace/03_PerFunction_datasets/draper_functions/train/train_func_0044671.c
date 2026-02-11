mime_message_construct_from_parser_sync (CamelMimePart *dw,
                                         CamelMimeParser *mp,
                                         GCancellable *cancellable,
                                         GError **error)
{
	CamelMimePartClass *mime_part_class;
	gchar *buf;
	gsize len;
	gint state;
	gint err;
	gboolean success;


	mime_part_class = CAMEL_MIME_PART_CLASS (camel_mime_message_parent_class);
	success = mime_part_class->construct_from_parser_sync (
		dw, mp, cancellable, error);

	if (!success)
		return FALSE;


	state = camel_mime_parser_step (mp, &buf, &len);
	switch (state) {
	case CAMEL_MIME_PARSER_STATE_EOF:
	case CAMEL_MIME_PARSER_STATE_FROM_END:

		camel_mime_parser_unstep (mp);
	case CAMEL_MIME_PARSER_STATE_MESSAGE_END:
		break;
	default:
		g_error ("Bad parser state: Expecing MESSAGE_END or EOF or EOM, got: %u", camel_mime_parser_state (mp));
		camel_mime_parser_unstep (mp);
		return FALSE;
	}

	err = camel_mime_parser_errno (mp);
	if (err != 0) {
		errno = err;
		g_set_error (
			error, G_IO_ERROR,
			g_io_error_from_errno (errno),
			"%s", g_strerror (errno));
		success = FALSE;
	}

	return success;
}
