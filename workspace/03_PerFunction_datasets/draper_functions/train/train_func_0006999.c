hook_parser_get_lex_stuff (pTHX) {
	if (NOT_PARSING || !PL_lex_stuff) {
		return NULL;
	}

	return SvPVX (PL_lex_stuff);
}
