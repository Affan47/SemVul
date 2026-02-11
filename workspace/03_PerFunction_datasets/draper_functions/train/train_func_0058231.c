add_char2buf(c, s)
    int		c;
    char_u	*s;
{
#ifdef FEAT_MBYTE
    char_u	temp[MB_MAXBYTES];
    int		i;
    int		len;

    len = (*mb_char2bytes)(c, temp);
    for (i = 0; i < len; ++i)
    {
	c = temp[i];
#endif

	if (c == K_SPECIAL)
	{
	    *s++ = K_SPECIAL;
	    *s++ = KS_SPECIAL;
	    *s++ = KE_FILLER;
	}
#ifdef FEAT_GUI
	else if (c == CSI)
	{
	    *s++ = CSI;
	    *s++ = KS_EXTRA;
	    *s++ = (int)KE_CSI;
	}
#endif
	else
	    *s++ = c;
#ifdef FEAT_MBYTE
    }
#endif
    return s;
}
