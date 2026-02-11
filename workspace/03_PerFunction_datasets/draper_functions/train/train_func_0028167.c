convert_to_utf32 (unsigned char *text)
{
	int text_len;
	int rlen;

	if (!text) {
	    return 0;
	}

	text_len = strlen(text);

	if (!text_len) {
	    return 0;
	}

	rlen = (int) parse_utf8(text, text_len, chunk_buffer_uni, text_len);

	return (rlen);
}
