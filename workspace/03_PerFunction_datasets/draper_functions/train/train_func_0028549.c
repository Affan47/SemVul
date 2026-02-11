reconstruct_message_part (GMimeMessagePart *msgpart, const char *uid, const char *spec)
{
	GMimeMessage *message;
	GMimeParser *parser;
	GMimeStream *stream;
	char *filename;
	int fd;

	filename = g_strdup_printf ("%s/%s.TEXT", uid, spec);
	if ((fd = open (filename, O_RDONLY, 0))) {
		g_mime_message_part_set_message (msgpart, NULL);
		g_free (filename);
		return;
	}

	g_free (filename);

	stream = g_mime_stream_fs_new (fd);
	parser = g_mime_parser_new_with_stream (stream);
	g_mime_parser_set_scan_from (parser, FALSE);
	g_object_unref (stream);

	message = g_mime_parser_construct_message (parser);
	g_object_unref (parser);

	g_mime_message_part_set_message (msgpart, message);
	g_object_unref (message);
}
