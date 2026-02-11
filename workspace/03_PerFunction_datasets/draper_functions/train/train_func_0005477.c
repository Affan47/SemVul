parser_scan_message_part (GMimeParser *parser, GMimeMessagePart *mpart, int *found)
{
	struct _GMimeParserPrivate *priv = parser->priv;
	ContentType *content_type;
	GMimeMessage *message;
	GMimeObject *object;
	GMimeStream *stream;
	HeaderRaw *header;

	g_assert (priv->state == GMIME_PARSER_STATE_CONTENT);

	if (priv->bounds != NULL) {

		register char *inptr;
		size_t atleast;
		char *inend;


		atleast = MAX (SCAN_HEAD, MAX_BOUNDARY_LEN (priv->bounds));

		if (parser_fill (parser, atleast) <= 0) {
			*found = FOUND_EOS;
			return;
		}

		inptr = priv->inptr;
		inend = priv->inend;

		*inend = '\n';

		while (*inptr != '\n')
			inptr++;

		*found = check_boundary (priv, priv->inptr, inptr - priv->inptr);
		switch (*found) {
		case FOUND_END_BOUNDARY:

			if (strncmp (priv->inptr, "From ", 5) != 0)
				return;
			break;
		case FOUND_BOUNDARY:
			return;
		}
	}


	priv->state = GMIME_PARSER_STATE_HEADERS;
	if (parser_step (parser) == GMIME_PARSER_STATE_ERROR) {


		*found = FOUND_EOS;
		return;
	}

	message = g_mime_message_new (FALSE);
	header = priv->headers;
	while (header) {
		if (g_ascii_strncasecmp (header->name, "Content-", 8) != 0)
			g_mime_object_append_header ((GMimeObject *) message, header->name, header->value);
		header = header->next;
	}

	content_type = parser_content_type (parser, NULL);
	if (content_type_is_type (content_type, "multipart", "*"))
		object = parser_construct_multipart (parser, content_type, TRUE, found);
	else
		object = parser_construct_leaf_part (parser, content_type, TRUE, found);

	content_type_destroy (content_type);
	message->mime_part = object;


	if ((stream = g_mime_header_list_get_stream (object->headers)))
		g_mime_header_list_set_stream (((GMimeObject *) message)->headers, stream);

	g_mime_message_part_set_message (mpart, message);
	g_object_unref (message);
}
