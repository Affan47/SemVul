do_marks(eap)
    exarg_T	*eap;
{
    char_u	*arg = eap->arg;
    int		i;
    char_u	*name;

    if (arg != NULL && *arg == NUL)
	arg = NULL;

    show_one_mark('\'', arg, &curwin->w_pcmark, NULL, TRUE);
    for (i = 0; i < NMARKS; ++i)
	show_one_mark(i + 'a', arg, &curbuf->b_namedm[i], NULL, TRUE);
    for (i = 0; i < NMARKS + EXTRA_MARKS; ++i)
    {
	if (namedfm[i].fmark.fnum != 0)
	    name = fm_getname(&namedfm[i].fmark, 15);
	else
	    name = namedfm[i].fname;
	if (name != NULL)
	{
	    show_one_mark(i >= NMARKS ? i - NMARKS + '0' : i + 'A',
		    arg, &namedfm[i].fmark.mark, name,
		    namedfm[i].fmark.fnum == curbuf->b_fnum);
	    if (namedfm[i].fmark.fnum != 0)
		vim_free(name);
	}
    }
    show_one_mark('"', arg, &curbuf->b_last_cursor, NULL, TRUE);
    show_one_mark('[', arg, &curbuf->b_op_start, NULL, TRUE);
    show_one_mark(']', arg, &curbuf->b_op_end, NULL, TRUE);
    show_one_mark('^', arg, &curbuf->b_last_insert, NULL, TRUE);
    show_one_mark('.', arg, &curbuf->b_last_change, NULL, TRUE);
#ifdef FEAT_VISUAL
    show_one_mark('<', arg, &curbuf->b_visual.vi_start, NULL, TRUE);
    show_one_mark('>', arg, &curbuf->b_visual.vi_end, NULL, TRUE);
#endif
    show_one_mark(-1, arg, NULL, NULL, FALSE);
}
