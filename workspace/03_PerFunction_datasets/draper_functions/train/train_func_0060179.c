parse_graf_n(struct parser *p) {
	graphics_mode *list = parser_priv(p);
	graphics_mode *mode = mem_zalloc(sizeof(graphics_mode));
	if (!mode) {
		return PARSE_ERROR_OUT_OF_MEMORY;
	}
	mode->pNext = list;
	mode->grafID = parser_getuint(p, "index");
	strncpy(mode->menuname, parser_getstr(p, "menuname"), 32);

	mode->alphablend = 0;
	mode->overdrawRow = 0;
	mode->overdrawMax = 0;
	strncpy(mode->file, "", 32);
	strncpy(mode->pref, "none", 32);

	parser_setpriv(p, mode);
	return PARSE_ERROR_NONE;
}
