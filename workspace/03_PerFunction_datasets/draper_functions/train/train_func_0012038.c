do_replace(void)
{
    filestruct *edittop_save, *begin;
    size_t begin_x, pww_save;
    bool meta_key = FALSE, func_key = FALSE;
    ssize_t numreplaced;
    int i;

    if (ISSET(VIEW_MODE)) {
	print_view_warning();
	search_replace_abort();
	return;
    }

    i = search_init(TRUE, FALSE);
    if (i == -1) {


	search_replace_abort();
	return;
    } else if (i == -2) {

	do_search();
	return;
    } else if (i == 1)

	do_replace();

    if (i != 0)
	return;


    if (answer[0] != '\0') {
#ifndef NANO_TINY
	update_history(&search_history, answer);
#endif
	last_search = mallocstrcpy(last_search, answer);
    }

    last_replace = mallocstrcpy(last_replace, "");

    i = do_prompt(FALSE,
#ifndef DISABLE_TABCOMP
	TRUE,
#endif
	MREPLACE2, last_replace,
	&meta_key, &func_key,
#ifndef NANO_TINY
	&replace_history,
#endif
	edit_refresh, _("Replace with"));

#ifndef NANO_TINY


    if (i == 0)
	update_history(&replace_history, answer);
#endif

    if (i != 0 && i != -2) {
	if (i == -1) {
	    if (last_replace[0] != '\0')
		answer = mallocstrcpy(answer, last_replace);
	    statusbar(_("Cancelled"));
	}
	search_replace_abort();
	return;
    }

    last_replace = mallocstrcpy(last_replace, answer);


    edittop_save = openfile->edittop;
    begin = openfile->current;
    begin_x = openfile->current_x;
    pww_save = openfile->placewewant;

    numreplaced = do_replace_loop(
#ifndef DISABLE_SPELLER
	FALSE,
#endif
	NULL, begin, &begin_x, last_search);


    openfile->edittop = edittop_save;
    openfile->current = begin;
    openfile->current_x = begin_x;
    openfile->placewewant = pww_save;

    edit_refresh();

    if (numreplaced >= 0)
	statusbar(P_("Replaced %lu occurrence",
		"Replaced %lu occurrences", (unsigned long)numreplaced),
		(unsigned long)numreplaced);

    search_replace_abort();
}
