config_parse(diskfile_backend *cfg_file, unsigned int level)
{
	int c;
	char *current_section = NULL;
	char *var_name;
	char *var_value;
	cvar_t *var, *existing;
	git_buf buf = GIT_BUF_INIT;
	int result = 0;
	khiter_t pos;


	cfg_file->reader.read_ptr = cfg_file->reader.buffer.ptr;
	cfg_file->reader.eof = 0;


	if (*cfg_file->reader.read_ptr == '\0')
		return 0;

	skip_bom(cfg_file);

	while (result == 0 && !cfg_file->reader.eof) {

		c = cfg_peek(cfg_file, SKIP_WHITESPACE);

		switch (c) {
		case '\n':
			cfg_file->reader.eof = 1;
			break;

		case '[':
			git__free(current_section);
			current_section = NULL;
			result = parse_section_header(cfg_file, &current_section);
			break;

		case ';':
		case '#':
			cfg_consume_line(cfg_file);
			break;

		default:
			result = parse_variable(cfg_file, &var_name, &var_value);
			if (result < 0)
				break;

			var = git__malloc(sizeof(cvar_t));
			GITERR_CHECK_ALLOC(var);
			memset(var, 0x0, sizeof(cvar_t));
			var->entry = git__malloc(sizeof(git_config_entry));
			GITERR_CHECK_ALLOC(var->entry);
			memset(var->entry, 0x0, sizeof(git_config_entry));

			git__strtolower(var_name);
			git_buf_printf(&buf, "%s.%s", current_section, var_name);
			git__free(var_name);

			if (git_buf_oom(&buf))
				return -1;

			var->entry->name = git_buf_detach(&buf);
			var->entry->value = var_value;
			var->entry->level = level;


			pos = git_strmap_lookup_index(cfg_file->values, var->entry->name);
			if (!git_strmap_valid_index(cfg_file->values, pos)) {
				git_strmap_insert(cfg_file->values, var->entry->name, var, result);
				if (result < 0)
					break;
				result = 0;
			} else {
				existing = git_strmap_value_at(cfg_file->values, pos);
				while (existing->next != NULL) {
					existing = existing->next;
				}
				existing->next = var;
			}

			break;
		}
	}

	git__free(current_section);
	return result;
}
