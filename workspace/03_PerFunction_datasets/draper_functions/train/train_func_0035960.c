write_viminfo_marks(fp_out)
    FILE	*fp_out;
{
    int		count;
    buf_T	*buf;
    int		is_mark_set;
    int		i;
#ifdef FEAT_WINDOWS
    win_T	*win;
    tabpage_T	*tp;


    FOR_ALL_TAB_WINDOWS(tp, win)
	set_last_cursor(win);
#else
	set_last_cursor(curwin);
#endif

    fprintf(fp_out, _("\n# History of marks within files (newest to oldest):\n"));
    count = 0;
    for (buf = firstbuf; buf != NULL; buf = buf->b_next)
    {


	if (buf->b_marks_read)
	{
	    if (buf->b_last_cursor.lnum != 0)
		is_mark_set = TRUE;
	    else
	    {
		is_mark_set = FALSE;
		for (i = 0; i < NMARKS; i++)
		    if (buf->b_namedm[i].lnum != 0)
		    {
			is_mark_set = TRUE;
			break;
		    }
	    }
	    if (is_mark_set && buf->b_ffname != NULL
		      && buf->b_ffname[0] != NUL && !removable(buf->b_ffname))
	    {
		home_replace(NULL, buf->b_ffname, IObuff, IOSIZE, TRUE);
		fprintf(fp_out, "\n> ");
		viminfo_writestring(fp_out, IObuff);
		write_one_mark(fp_out, '"', &buf->b_last_cursor);
		write_one_mark(fp_out, '^', &buf->b_last_insert);
		write_one_mark(fp_out, '.', &buf->b_last_change);
#ifdef FEAT_JUMPLIST

		for (i = 0; i < buf->b_changelistlen; ++i)
		    write_one_mark(fp_out, '+', &buf->b_changelist[i]);
#endif
		for (i = 0; i < NMARKS; i++)
		    write_one_mark(fp_out, 'a' + i, &buf->b_namedm[i]);
		count++;
	    }
	}
    }

    return count;
}
