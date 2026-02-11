StrToUtf8(const char *in)
{
	unsigned int n, i = 0;
	char *result = NULL;


	if (g_utf8_validate(in, -1, NULL))
		return (char *)in;

	eb_debug(DBG_CORE, "Converting %s\n", in);

	result = (char *)malloc(strlen(in) * 2 + 1);


	for (n = 0; n < strlen(in); n++) {
		unsigned char c = (unsigned char)in[n];

		if (c < 128) {
			result[i++] = (char)c;
		} else {
			result[i++] = (char)((c >> 6) | 192);
			result[i++] = (char)((c & 63) | 128);
		}
	}
	result[i] = '\0';
	return result;
}
