vcol2col(wp, lnum, vcol)
    win_T	*wp;
    linenr_T	lnum;
    int		vcol;
{

    int		count = 0;
    char_u	*ptr;
    char_u	*start;

    start = ptr = ml_get_buf(wp->w_buffer, lnum, FALSE);
    while (count < vcol && *ptr != NUL)
    {
	count += win_lbr_chartabsize(wp, ptr, count, NULL);
	mb_ptr_adv(ptr);
    }
    return (int)(ptr - start);
}
