config_set(git_config_file *cfg, const char *name, const char *value)
{
	cvar_t *var = NULL, *old_var;
	diskfile_backend *b = (diskfile_backend *)cfg;
	char *key;
	khiter_t pos;
	int rval;

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

		if (value) {
			tmp = git__strdup(value);
			GITERR_CHECK_ALLOC(tmp);
		}

		git__free(existing->value);
		existing->value = tmp;

		return config_write(b, existing->key, NULL, value);
	}

	var = git__malloc(sizeof(cvar_t));
	GITERR_CHECK_ALLOC(var);

	memset(var, 0x0, sizeof(cvar_t));

	var->key = key;
	var->value = NULL;

	if (value) {
		var->value = git__strdup(value);
		GITERR_CHECK_ALLOC(var->value);
	}

	if (config_write(b, key, NULL, value) < 0) {
		cvar_free(var);
		return -1;
	}

	git_strmap_insert2(b->values, key, var, old_var, rval);
	if (rval < 0)
		return -1;
	if (old_var != NULL)
		cvar_free(old_var);

	return 0;
}
