config_parse(CONFIG_REC *rec)
{
	int fd;

	g_return_val_if_fail(rec != NULL, -1);
	g_return_val_if_fail(rec->fname != NULL, -1);

	fd = open(rec->fname, O_RDONLY);
	if (fd == -1)
		return config_error(rec, g_strerror(errno));

	config_parse_init(rec, rec->fname);
	g_scanner_input_file(rec->scanner, fd);
	config_parse_loop(rec, rec->mainnode, G_TOKEN_EOF);
	g_scanner_destroy(rec->scanner);

	close(fd);

	return rec->last_error == NULL ? 0 : -1;
}
