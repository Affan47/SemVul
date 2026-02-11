config_parse_loop(CONFIG_REC *rec, CONFIG_NODE *node, GTokenType expect)
{
	GTokenType expected_token;

	g_return_if_fail(rec != NULL);
	g_return_if_fail(node != NULL);

	for (;;) {
		config_parse_peek_token(rec->scanner, node);
		if (rec->scanner->next_token == expect ||
		    rec->scanner->next_token == G_TOKEN_EOF) break;

		expected_token = config_parse_symbol(rec, node);
		if (expected_token != G_TOKEN_NONE) {
			if (expected_token == G_TOKEN_ERROR)
				expected_token = G_TOKEN_NONE;
			g_scanner_unexp_token(rec->scanner, expected_token, NULL, "symbol", NULL, NULL, TRUE);
		}
	}
}
