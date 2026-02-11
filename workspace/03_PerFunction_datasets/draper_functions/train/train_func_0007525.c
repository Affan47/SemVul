write_content (GMimePart *part, GMimeStream *stream)
{
	ssize_t nwritten, total = 0;

	if (!part->content)
		return 0;


	if (part->encoding != g_mime_data_wrapper_get_encoding (part->content)) {
		GMimeStream *filtered_stream;
		const char *filename;
		GMimeFilter *filter;

		switch (part->encoding) {
		case GMIME_CONTENT_ENCODING_UUENCODE:
			filename = g_mime_part_get_filename (part);
			nwritten = g_mime_stream_printf (stream, "begin 0644 %s\n",
							 filename ? filename : "unknown");
			if (nwritten == -1)
				return -1;

			total += nwritten;


		case GMIME_CONTENT_ENCODING_QUOTEDPRINTABLE:
		case GMIME_CONTENT_ENCODING_BASE64:
			filtered_stream = g_mime_stream_filter_new (stream);
			filter = g_mime_filter_basic_new (part->encoding, TRUE);
			g_mime_stream_filter_add (GMIME_STREAM_FILTER (filtered_stream), filter);
			g_object_unref (filter);
			break;
		default:
			filtered_stream = stream;
			g_object_ref (stream);
			break;
		}

		nwritten = g_mime_data_wrapper_write_to_stream (part->content, filtered_stream);
		g_mime_stream_flush (filtered_stream);
		g_object_unref (filtered_stream);

		if (nwritten == -1)
			return -1;

		total += nwritten;

		if (part->encoding == GMIME_CONTENT_ENCODING_UUENCODE) {

			nwritten = g_mime_stream_write (stream, "end\n", 4);
			if (nwritten == -1)
				return -1;

			total += nwritten;
		}
	} else {
		GMimeStream *content_stream;

		content_stream = g_mime_data_wrapper_get_stream (part->content);
		g_mime_stream_reset (content_stream);
		nwritten = g_mime_stream_write_to_stream (content_stream, stream);
		g_mime_stream_reset (content_stream);

		if (nwritten == -1)
			return -1;

		total += nwritten;
	}

	return total;
}
