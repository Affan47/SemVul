mb_unescape(pp)
    char_u **pp;
{
    static char_u	buf[MB_MAXBYTES + 1];
    int			n, m = 0;
    char_u		*str = *pp;


    for (n = 0; str[n] != NUL && m <= MB_MAXBYTES; ++n)
    {
	if (str[n] == K_SPECIAL
		&& str[n + 1] == KS_SPECIAL
		&& str[n + 2] == KE_FILLER)
	{
	    buf[m++] = K_SPECIAL;
	    n += 2;
	}
	else if ((str[n] == K_SPECIAL
# ifdef FEAT_GUI
		    || str[n] == CSI
# endif
		 )
		&& str[n + 1] == KS_EXTRA
		&& str[n + 2] == (int)KE_CSI)
	{
	    buf[m++] = CSI;
	    n += 2;
	}
	else if (str[n] == K_SPECIAL
# ifdef FEAT_GUI
		|| str[n] == CSI
# endif
		)
	    break;
	else
	    buf[m++] = str[n];
	buf[m] = NUL;


	if ((*mb_ptr2len)(buf) > 1)
	{
	    *pp = str + n + 1;
	    return buf;
	}
    }
    return NULL;
}
