dico_markup_register(const char *name)
{
    if (!dico_markup_valid_name_p(name))
	return EINVAL;

    if (!dico_markup_list) {
	dico_markup_list = dico_list_create();
	if (!dico_markup_list)
	    return ENOMEM;
	dico_list_set_comparator(dico_markup_list, cmp_markup_name);
    }

    if (!dico_markup_lookup(name)) {
	char *s = strdup(name);
	if (!s)
	    return ENOMEM;
	return dico_list_append(dico_markup_list, s);
    }
    return 0;
}
