shell_emit_file_list(shell_ty *sh, string_list_ty *slp)
{
    symtab_ty       *stp;
    size_t          j;
    size_t          longest;


    if (slp->nstrings == 0)
	return;


    longest = slp->string[0]->str_length;
    for (j = 1; j < slp->nstrings; ++j)
    {
	size_t          n;

	n = how_much_in_common(slp->string[0], slp->string[j]);
	if (n < longest)
	    longest = n;
    }


    stp = symtab_alloc(slp->nstrings);
    for (j = 0; j < slp->nstrings; ++j)
    {
	string_ty       *s;

	s = following_slash(slp->string[j], longest);
	if (symtab_query(stp, s))
	{
	    str_free(s);
	    continue;
	}
	shell_emit(sh, s);
	symtab_assign(stp, s, s);
	str_free(s);
    }
    symtab_free(stp);
}
