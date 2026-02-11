add_pattern_node(struct ast_context *con, struct match_char *current, const struct pattern_node *pattern, int is_pattern, int already, struct match_char **nextcharptr)
{
	struct match_char *m;

	if (!(m = ast_calloc(1, sizeof(*m) + strlen(pattern->buf)))) {
		return NULL;
	}


	strcpy(m->x, pattern->buf);


	m->is_pattern = is_pattern;
	if (pattern->specif == 1 && is_pattern && pattern->buf[0] == 'N') {
		m->specificity = 0x0832;
	} else if (pattern->specif == 1 && is_pattern && pattern->buf[0] == 'Z') {
		m->specificity = 0x0931;
	} else if (pattern->specif == 1 && is_pattern && pattern->buf[0] == 'X') {
		m->specificity = 0x0a30;
	} else if (pattern->specif == 1 && is_pattern && pattern->buf[0] == '.') {
		m->specificity = 0x18000;
	} else if (pattern->specif == 1 && is_pattern && pattern->buf[0] == '!') {
		m->specificity = 0x28000;
	} else {
		m->specificity = pattern->specif;
	}

	if (!con->pattern_tree) {
		insert_in_next_chars_alt_char_list(&con->pattern_tree, m);
	} else {
		if (already) {
			insert_in_next_chars_alt_char_list(nextcharptr, m);
		} else {
			insert_in_next_chars_alt_char_list(&current->next_char, m);
		}
	}

	return m;
}
