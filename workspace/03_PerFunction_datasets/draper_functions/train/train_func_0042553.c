im_preedit_changed_cb(GtkIMContext *context, gpointer data UNUSED)
{
    char    *preedit_string = NULL;
    int	    cursor_index    = 0;
    int	    num_move_back   = 0;
    char_u  *str;
    char_u  *p;
    int	    i;

    gtk_im_context_get_preedit_string(context,
				      &preedit_string, NULL,
				      &cursor_index);

#ifdef XIM_DEBUG
    xim_log("im_preedit_changed_cb(): %s\n", preedit_string);
#endif

    g_return_if_fail(preedit_string != NULL);


    if (preedit_start_col == MAXCOL && preedit_string[0] != '\0')
    {
	xim_has_preediting = TRUE;


	init_preedit_start_col();
    }
    else if (cursor_index == 0 && preedit_string[0] == '\0')
    {
	xim_has_preediting = FALSE;


	preedit_start_col = MAXCOL;
    }

    im_delete_preedit();


    if (preedit_start_col != MAXCOL)
	preedit_end_col = preedit_start_col;
    str = (char_u *)preedit_string;
    for (p = str, i = 0; *p != NUL; p += utf_byte2len(*p), ++i)
    {
	int is_composing;

	is_composing = ((*p & 0x80) != 0 && utf_iscomposing(utf_ptr2char(p)));


	if (!is_composing || p_deco)
	{
	    if (i < cursor_index)
		++im_preedit_cursor;
	    else
		++im_preedit_trailing;
	}
	if (!is_composing && i >= cursor_index)
	{


	    ++num_move_back;
	}
	if (preedit_start_col != MAXCOL)
	    preedit_end_col += utf_ptr2cells(p);
    }

    if (p > str)
    {
	im_add_to_input(str, (int)(p - str));
	im_correct_cursor(num_move_back);
    }

    g_free(preedit_string);

    if (gtk_main_level() > 0)
	gtk_main_quit();
}
