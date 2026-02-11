corr_ind_maxparen(ind_maxparen, startpos)
    int		ind_maxparen;
    pos_T	*startpos;
{
    long	n = (long)startpos->lnum - (long)curwin->w_cursor.lnum;

    if (n > 0 && n < ind_maxparen / 2)
	return ind_maxparen - (int)n;
    return ind_maxparen;
}
