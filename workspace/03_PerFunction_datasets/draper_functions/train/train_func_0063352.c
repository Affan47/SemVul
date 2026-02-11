profile_get_subsection_names(profile_t profile, const char **names,
								  char ***ret_names)
{
	long		retval;
	void			*state;
	char			*name;
	struct profile_string_list values;

	if ((retval = profile_iterator_create(profile, names,
		PROFILE_ITER_LIST_SECTION | PROFILE_ITER_SECTIONS_ONLY,
		&state)))
		return retval;

	if ((retval = init_list(&values)))
		return retval;

	do {
		if ((retval = profile_iterator(&state, &name, 0)))
			goto cleanup;
		if (name)
			add_to_list(&values, name);
	} while (state);

	end_list(&values, ret_names);
	return 0;

cleanup:
	end_list(&values, 0);
	return retval;
}
