os_xargs(string_ty *the_command, string_list_ty *the_list, string_ty *dir)
{
    enum { chunk = 50 };
    size_t          j;

    for (j = 0; j < the_list->nstrings; j += chunk)
    {
	size_t          nargs;
	size_t          k;
	string_ty       *s;

	nargs = chunk;
	if (j + nargs > the_list->nstrings)
	    nargs = the_list->nstrings - j;
	string_list_ty wl;
	wl.push_back(the_command);
	for (k = 0; k < nargs; ++k)
	{
	    s = str_quote_shell(the_list->string[j + k]);
	    wl.push_back(s);
	    str_free(s);
	}
	s = wl.unsplit();
	os_become_orig();
	os_execute(s, OS_EXEC_FLAG_INPUT, dir);
	os_become_undo();
	str_free(s);
    }
}
