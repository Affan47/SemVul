dis_msg(p, skip_esc)
    char_u	*p;
    int		skip_esc;
{
    int		n;
#ifdef FEAT_MBYTE
    int		l;
#endif

    n = (int)Columns - 6;
    while (*p != NUL
	    && !(*p == ESC && skip_esc && *(p + 1) == NUL)
	    && (n -= ptr2cells(p)) >= 0)
    {
#ifdef FEAT_MBYTE
	if (has_mbyte && (l = (*mb_ptr2len)(p)) > 1)
	{
	    msg_outtrans_len(p, l);
	    p += l;
	}
	else
#endif
	    msg_outtrans_len(p++, 1);
    }
    ui_breakcheck();
}
