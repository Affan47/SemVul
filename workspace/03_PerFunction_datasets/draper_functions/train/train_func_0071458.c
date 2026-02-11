parse_c_a(struct parser *p) {
	struct player_class *c = parser_priv(p);

	if (!c)
		return PARSE_ERROR_MISSING_RECORD_HEADER;
	c->max_attacks = parser_getint(p, "max-attacks");
	c->min_weight = parser_getint(p, "min-weight");
	c->att_multiply = parser_getint(p, "att-multiply");
	return PARSE_ERROR_NONE;
}
