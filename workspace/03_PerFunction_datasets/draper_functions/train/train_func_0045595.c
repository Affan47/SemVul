matcherlist_skip_headers(FILE *fp)
{
	gchar buf[BUFFSIZE];

	while (procheader_get_one_field(buf, sizeof(buf), fp, NULL) != -1)
		;
}
