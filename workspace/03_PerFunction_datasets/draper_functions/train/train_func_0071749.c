prnt_mtchs(regex_t *exp, const char *filename, const char *stream, regmatch_t *pmatch, regmatch_t *nl_offset, int num, int lines, int options) {
	int i;
	int j = 0;
	int ln_cnt;
	int begin;
	int o_begin;
	char *str;

	o_begin = -1;
	ln_cnt = 0;
	for(i = 0; i < num; i++) {
		str = extract_line(stream, pmatch[i].rm_so, pmatch[i].rm_eo, &begin);
		if(begin > o_begin) {
			if(!(options & JG_WORD_EXPRESSIONS) || chk_wrd(exp, str)) {
				ln_cnt++;
				if(!(options & JG_PRINT_COUNT)) {
					printf("%s:", filename);
					if(options & JG_PRINT_LINE_NUMBER) {
						for(; j < lines && nl_offset[j].rm_so < begin; j++);
						printf("%d:", j + 1);
					}
					if(options & JG_PRINT_BYTEOFFSET) printf("%d:", begin);
					printf("%s\n", str);
				}
			}
		}
		o_begin = begin;
		free(str);
	}
	if(options & JG_PRINT_COUNT) printf("%s:%d\n", filename, ln_cnt);
}
