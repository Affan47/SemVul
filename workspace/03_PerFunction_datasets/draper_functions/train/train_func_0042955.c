regex_playlist_test(regex_playlist_t* rep, const ucs2_char_t* filename)
{
	size_t i;
	int value = 0;
	for (i = 0;i < rep->num_conditions;++i) {
		regex_condition_t* cond = &rep->conditions[i];
		if (cond->regex_pattern) {
			char *mbs = ucs2dupmbs(filename);
			if (mbs) {
				if (regexec(&cond->reg, mbs, 0, NULL, 0) == 0) {
					value = cond->value;
				}
				ucs2free(mbs);
			}
		} else {
			ucs2_char_t* ucs2 = ucs2dup(filename);
			if (ucs2) {
				ucs2lwr(ucs2);
				if (ucs2str(ucs2, cond->str)) {
					value = cond->value;
				}
				ucs2free(ucs2);
			}
		}
	}
	return value;
}
