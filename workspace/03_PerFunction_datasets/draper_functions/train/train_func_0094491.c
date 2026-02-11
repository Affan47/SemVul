do_gotolinecolumn(ssize_t line, ssize_t column, bool use_answer,
	bool interactive, bool save_pos, bool allow_update)
{
    bool meta_key = FALSE, func_key = FALSE;
    const sc *s;

    if (interactive) {
	char *ans = mallocstrcpy(NULL, answer);


	int i = do_prompt(FALSE,
#ifndef DISABLE_TABCOMP
		TRUE,
#endif
		MGOTOLINE, use_answer ? ans : "",
		&meta_key, &func_key,
#ifndef NANO_TINY
		NULL,
#endif
		edit_refresh, _("Enter line number, column number"));

	free(ans);


	if (i < 0) {
	    statusbar(_("Cancelled"));
	    display_main_list();
	    return;
	}


	s = get_shortcut(currmenu, &i, &meta_key, &func_key);
	if (s && s->scfunc ==  GOTOTEXT_MSG) {

	    search_init(TRUE, TRUE);

	    do_search();
	    return;
	}


	if (!parse_line_column(answer, &line, &column) || line < 1 ||
		column < 1) {
	    if (i == 0)
		statusbar(_("Invalid line or column number"));
	    display_main_list();
	    return;
	}
    } else {
	if (line < 1)
	    line = openfile->current->lineno;

	if (column < 1)
	    column = openfile->placewewant + 1;
    }

    for (openfile->current = openfile->fileage;
	openfile->current != openfile->filebot && line > 1; line--)
	openfile->current = openfile->current->next;

    openfile->current_x = actual_x(openfile->current->data, column - 1);
    openfile->placewewant = column - 1;


    edit_update(save_pos ? NONE : CENTER);


    if (allow_update)
	edit_refresh();

    display_main_list();
}
