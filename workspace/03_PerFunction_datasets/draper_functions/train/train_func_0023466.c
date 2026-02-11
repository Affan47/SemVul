ins_compl_addfrommatch()
{
    char_u	*p;
    int		len = curwin->w_cursor.col - compl_col;
    int		c;
    compl_T	*cp;

    p = compl_shown_match->cp_str;
    if ((int)STRLEN(p) <= len)
    {


	if (compl_shown_match->cp_flags & ORIGINAL_TEXT)
	{
	    p = NULL;
	    for (cp = compl_shown_match->cp_next; cp != NULL
				 && cp != compl_first_match; cp = cp->cp_next)
	    {
		if (compl_leader == NULL
			|| ins_compl_equal(cp, compl_leader,
						   (int)STRLEN(compl_leader)))
		{
		    p = cp->cp_str;
		    break;
		}
	    }
	    if (p == NULL || (int)STRLEN(p) <= len)
		return;
	}
	else
	    return;
    }
    p += len;
#ifdef FEAT_MBYTE
    c = mb_ptr2char(p);
#else
    c = *p;
#endif
    ins_compl_addleader(c);
}
