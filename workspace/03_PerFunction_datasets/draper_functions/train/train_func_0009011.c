unset_local_var_len(const char *name, int name_len)
{
	struct variable *cur;
	struct variable **var_pp;

	if (!name)
		return EXIT_SUCCESS;
	var_pp = &G.top_var;
	while ((cur = *var_pp) != NULL) {
		if (strncmp(cur->varstr, name, name_len) == 0 && cur->varstr[name_len] == '=') {
			if (cur->flg_read_only) {
				bb_error_msg("%s: readonly variable", name);
				return EXIT_FAILURE;
			}
			*var_pp = cur->next;
			debug_printf_env("%s: unsetenv '%s'\n", __func__, cur->varstr);
			bb_unsetenv(cur->varstr);
			if (name_len == 3 && cur->varstr[0] == 'P' && cur->varstr[1] == 'S')
				cmdedit_update_prompt();
			if (!cur->max_len)
				free(cur->varstr);
			free(cur);
			return EXIT_SUCCESS;
		}
		var_pp = &cur->next;
	}
	return EXIT_SUCCESS;
}
