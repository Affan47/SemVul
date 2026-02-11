aspell_provider_list_dicts (EnchantProvider * me,
			    size_t * out_n_dicts)
{
	PspellConfig * spell_config;
	AspellDictInfoList * dlist;
	AspellDictInfoEnumeration * dels;
	const AspellDictInfo * entry;
	char ** out_list = NULL;

	spell_config = new_pspell_config ();

	dlist = get_aspell_dict_info_list (spell_config);

	*out_n_dicts = 0;
	dels = aspell_dict_info_list_elements (dlist);


	while ( (entry = aspell_dict_info_enumeration_next(dels)) != 0)
		(*out_n_dicts)++;

	if (*out_n_dicts) {
		size_t i;

		out_list = g_new0 (char *, *out_n_dicts + 1);
		dels = aspell_dict_info_list_elements (dlist);

		for (i = 0; i < *out_n_dicts; i++) {
			entry = aspell_dict_info_enumeration_next (dels);

			out_list[i] = g_strdup (entry->code);
		}

		delete_aspell_dict_info_enumeration (dels);
	}

	delete_pspell_config (spell_config);

	return out_list;
}
