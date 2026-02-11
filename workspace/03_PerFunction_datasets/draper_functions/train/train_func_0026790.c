free_lexer_rules()
{
	for (int i=0; i<lexer_rules_count; i++) {
		if (lexer_rules[i].string_type==LRST_REGEX) {
			regfree((regex_t*)lexer_rules_precompiled[i]);
			free(lexer_rules_precompiled[i]);
		} else {
		}
	}
	free(lexer_rules_precompiled);
}
