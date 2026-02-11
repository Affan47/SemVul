linecopy(to, from, wp)
    int		to;
    int		from;
    win_T	*wp;
{
    unsigned	off_to = LineOffset[to] + wp->w_wincol;
    unsigned	off_from = LineOffset[from] + wp->w_wincol;

    mch_memmove(ScreenLines + off_to, ScreenLines + off_from,
	    wp->w_width * sizeof(schar_T));
# ifdef FEAT_MBYTE
    if (enc_utf8)
    {
	int	i;

	mch_memmove(ScreenLinesUC + off_to, ScreenLinesUC + off_from,
		wp->w_width * sizeof(u8char_T));
	for (i = 0; i < p_mco; ++i)
	    mch_memmove(ScreenLinesC[i] + off_to, ScreenLinesC[i] + off_from,
		    wp->w_width * sizeof(u8char_T));
    }
    if (enc_dbcs == DBCS_JPNU)
	mch_memmove(ScreenLines2 + off_to, ScreenLines2 + off_from,
		wp->w_width * sizeof(schar_T));
# endif
    mch_memmove(ScreenAttrs + off_to, ScreenAttrs + off_from,
	    wp->w_width * sizeof(sattr_T));
}
