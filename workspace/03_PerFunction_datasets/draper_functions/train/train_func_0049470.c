eulerrc_load(EulerPrefs *prefs)
{
	GScanner *scanner;
	gint fd;
	guint i, expected_token = G_TOKEN_NONE;
	gchar *filename;

	filename = g_strconcat(g_get_home_dir(),"/.euler/eulerrc",NULL);
	fd = open(filename, O_RDONLY);
	g_free(filename);
	if (fd < 0)	return 0;

	scanner = g_scanner_new(NULL);


	scanner->config->symbol_2_token = TRUE;


	scanner->config->identifier_2_string = TRUE;

	g_scanner_freeze_symbol_table(scanner);
	for (i = 0; i < n_symbols; i++)
		g_scanner_add_symbol(scanner,symbols[i].name,GINT_TO_POINTER(symbols[i].token));
	g_scanner_thaw_symbol_table(scanner);

	g_scanner_input_file(scanner, fd);
	scanner->input_name = ".eulerrc";


	while(1) {
		expected_token = eulerrc_parse(scanner,prefs);

		if (expected_token != G_TOKEN_NONE) {
			switch (expected_token) {
				case G_TOKEN_EQUAL_SIGN:
					g_scanner_unexp_token(scanner,expected_token,NULL,"=",NULL,NULL,TRUE);
					break;
				case G_TOKEN_EOF:
					break;
				default:
					g_scanner_unexp_token(scanner,expected_token,NULL,NULL,NULL,NULL,TRUE);
					break;
			}
			break;
		}
	}

	g_scanner_destroy(scanner);

	close(fd);

	return 1;
}
