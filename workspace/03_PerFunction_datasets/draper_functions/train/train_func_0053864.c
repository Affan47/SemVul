config_set(git_config_file *cfg, const char *name, const char *value)
{
	cvar_t *var = NULL, *old_var;
	diskfile_backend *b = (diskfile_backend *)cfg;
	char *key, *esc_value = NULL;
	khiter_t pos;
	int rval, ret;

	if (normalize_name(name, &key) < 0)
		return -1;


	pos = git_strmap_lookup_index(b->values, key);
	if (git_strmap_valid_index(b->values, pos)) {
		cvar_t *existing = git_strmap_value_at(b->values, pos);
		char *tmp = NULL;

		git__free(key);

		if (existing->next != NULL) {
			giterr_set(GITERR_CONFIG, "Multivar incompatible with simple set");
			return -1;
		}


		if ((!existing->entry->value && !value) ||
			(existing->entry->value && value && !strcmp(existing->entry->value, value)))
			return 0;

		if (value) {
			tmp = git__strdup(value);
			GITERR_CHECK_ALLOC(tmp);
			esc_value = escape_value(value);
			GITERR_CHECK_ALLOC(esc_value);
		}

		git__free((void *)existing->entry->value);
		existing->entry->value = tmp;

		ret = config_write(b, existing->entry->name, NULL, esc_value);

		git__free(esc_value);
		return ret;
	}

	var = git__malloc(sizeof(cvar_t));
	GITERR_CHECK_ALLOC(var);
	memset(var, 0x0, sizeof(cvar_t));
	var->entry = git__malloc(sizeof(git_config_entry));
	GITERR_CHECK_ALLOC(var->entry);
	memset(var->entry, 0x0, sizeof(git_config_entry));

	var->entry->name = key;
	var->entry->value = NULL;

	if (value) {
		var->entry->value = git__strdup(value);
		GITERR_CHECK_ALLOC(var->entry->value);
		esc_value = escape_value(value);
		GITERR_CHECK_ALLOC(esc_value);
	}

	if (config_write(b, key, NULL, esc_value) < 0) {
		git__free(esc_value);
		cvar_free(var);
		return -1;
	}

	git__free(esc_value);
	git_strmap_insert2(b->values, key, var, old_var, rval);
	if (rval < 0)
		return -1;
	if (old_var != NULL)
		cvar_free(old_var);

	return 0;
}
