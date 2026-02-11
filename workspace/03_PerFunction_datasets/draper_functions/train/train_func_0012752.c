get_value(snd_use_case_mgr_t *uc_mgr,
                     const char *identifier,
                     const char **value,
                     const char *modifier)
{
        struct use_case_modifier *mod;
	int err;

	if (modifier != NULL) {
	        mod = find_modifier(uc_mgr, modifier);
		if (mod != NULL) {
			err = get_value1(value, &mod->value_list, identifier);
			if (err >= 0 || err != -ENOENT)
				return err;
		}
	}
	err = get_value1(value, &uc_mgr->active_verb->value_list, identifier);
	if (err >= 0 || err != -ENOENT)
		return err;
	err = get_value1(value, &uc_mgr->value_list, identifier);
	if (err >= 0 || err != -ENOENT)
		return err;
	return -ENOENT;
}
