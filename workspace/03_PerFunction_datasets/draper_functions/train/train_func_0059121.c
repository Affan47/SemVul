pars_get_lex_chars(

	char*	buf,
	int*	result,
	int	max_size)

{
	int	len;

	len = pars_sym_tab_global->string_len
		- pars_sym_tab_global->next_char_pos;
	if (len == 0) {
#ifdef YYDEBUG

#endif
		*result = 0;

		return;
	}

	if (len > max_size) {
		len = max_size;
	}

#ifdef UNIV_SQL_DEBUG
	if (pars_print_lexed) {

		if (len >= 5) {
			len = 5;
		}

		fwrite(pars_sym_tab_global->sql_string
		       + pars_sym_tab_global->next_char_pos,
		       1, len, stderr);
	}
#endif

	ut_memcpy(buf, pars_sym_tab_global->sql_string
		  + pars_sym_tab_global->next_char_pos, len);
	*result = len;

	pars_sym_tab_global->next_char_pos += len;
}
