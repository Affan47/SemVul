tds_alloc_get_string(TDSSOCKET * tds, char **string, int len)
{
	char *s;
	int out_len;

	CHECK_TDS_EXTRA(tds);

	if (len < 0) {
		*string = NULL;
		return 0;
	}


	s = (char *) malloc(len * 4 + 1);
	out_len = tds_get_string(tds, len, s, len * 4);
	if (!s) {
		*string = NULL;
		return -1;
	}
	s = realloc(s, out_len + 1);
	s[out_len] = '\0';
	*string = s;
	return 0;
}
