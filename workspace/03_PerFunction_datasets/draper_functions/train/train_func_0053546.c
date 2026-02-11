parse_p_i(struct parser *p) {
	struct player_race *r = parser_priv(p);
	if (!r)
		return PARSE_ERROR_MISSING_RECORD_HEADER;
	r->history = findchart(histories, parser_getuint(p, "hist"));
	r->b_age = parser_getint(p, "b-age");
	r->m_age = parser_getint(p, "m-age");
	return PARSE_ERROR_NONE;
}
