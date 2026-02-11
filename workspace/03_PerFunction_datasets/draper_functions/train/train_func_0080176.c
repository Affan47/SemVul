get_http_header_value(const char *src) {
	char *sub;

	if ((sub = strchr(src, ':'))) {
		sub++;
		while (*sub == ' ')
			sub++;

		return strdup(sub);
	} else
		return NULL;
}
