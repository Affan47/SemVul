ins_compl_longest_match(match)
    compl_T	*match;
{
    char_u	*p, *s;
    int		c1, c2;
    int		had_match;

    if (compl_leader == NULL)
    {

	compl_leader = vim_strsave(match->cp_str);
	if (compl_leader != NULL)
	{
	    had_match = (curwin->w_cursor.col > compl_col);
	    ins_compl_delete();
	    ins_bytes(compl_leader + curwin->w_cursor.col - compl_col);
	    ins_redraw(FALSE);


	    if (!had_match)
		ins_compl_delete();
	    compl_used_match = FALSE;
	}
    }
    else
    {

	p = compl_leader;
	s = match->cp_str;
	while (*p != NUL)
	{
#ifdef FEAT_MBYTE
	    if (has_mbyte)
	    {
		c1 = mb_ptr2char(p);
		c2 = mb_ptr2char(s);
	    }
	    else
#endif
	    {
		c1 = *p;
		c2 = *s;
	    }
	    if (match->cp_icase ? (MB_TOLOWER(c1) != MB_TOLOWER(c2))
								 : (c1 != c2))
		break;
#ifdef FEAT_MBYTE
	    if (has_mbyte)
	    {
		mb_ptr_adv(p);
		mb_ptr_adv(s);
	    }
	    else
#endif
	    {
		++p;
		++s;
	    }
	}

	if (*p != NUL)
	{

	    *p = NUL;
	    had_match = (curwin->w_cursor.col > compl_col);
	    ins_compl_delete();
	    ins_bytes(compl_leader + curwin->w_cursor.col - compl_col);
	    ins_redraw(FALSE);


	    if (!had_match)
		ins_compl_delete();
	}

	compl_used_match = FALSE;
    }
}
