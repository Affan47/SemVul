perform(complete_ty *cp, shell_ty *sh)
{
    complete_project_delta_ty *this_thing;
    string_ty       *prefix;
    size_t          j;

    this_thing = (complete_project_delta_ty *)cp;
    prefix = shell_prefix_get(sh);
    for (j = 0; ; ++j)
    {
	long            cn;
	long            dn;
	string_list_ty  name;
	size_t		k;
	string_ty       *s;

	if (!project_history_nth(this_thing->pp, j, &cn, &dn, &name))
	    break;

	s = str_format("%ld", dn);
	if (str_leading_prefix(s, prefix))
	    shell_emit(sh, s);
	str_free(s);

	for (k = 0; k < name.nstrings; ++k)
	{
	    s = name.string[k];
	    if (str_leading_prefix(s, prefix))
		shell_emit(sh, s);
	}
    }
}
