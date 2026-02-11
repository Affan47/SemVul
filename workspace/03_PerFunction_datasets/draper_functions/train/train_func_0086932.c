convert_to_usc2le_string(TDSSOCKET * tds, const char *s, size_t len, char *out)
{
	const char *ib;
	char *ob;
	size_t il, ol;

	const TDSICONV * char_conv = tds->char_convs[client2ucs2];


	TDS_ERRNO_MESSAGE_FLAGS *suppress = (TDS_ERRNO_MESSAGE_FLAGS *) & char_conv->suppress;

	if (char_conv->flags == TDS_ENCODING_MEMCPY) {
		memcpy(out, s, len);
		return len;
	}


	ib = s;
	il = len;
	ob = out;
	ol = len * 2;
	memset(suppress, 0, sizeof(char_conv->suppress));
	if (tds_iconv(tds, char_conv, to_server, &ib, &il, &ob, &ol) == (size_t) - 1)
		return (size_t) -1;

	return ob - out;
}
