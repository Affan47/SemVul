spell_soundfold_sofo(slang, inword, res)
    slang_T	*slang;
    char_u	*inword;
    char_u	*res;
{
    char_u	*s;
    int		ri = 0;
    int		c;

#ifdef FEAT_MBYTE
    if (has_mbyte)
    {
	int	prevc = 0;
	int	*ip;


	for (s = inword; *s != NUL; )
	{
	    c = mb_cptr2char_adv(&s);
	    if (enc_utf8 ? utf_class(c) == 0 : vim_iswhite(c))
		c = ' ';
	    else if (c < 256)
		c = slang->sl_sal_first[c];
	    else
	    {
		ip = ((int **)slang->sl_sal.ga_data)[c & 0xff];
		if (ip == NULL)
		    c = NUL;
		else
		    for (;;)
		    {
			if (*ip == 0)
			{
			    c = NUL;
			    break;
			}
			if (*ip == c)
			{
			    c = ip[1];
			    break;
			}
			ip += 2;
		    }
	    }

	    if (c != NUL && c != prevc)
	    {
		ri += mb_char2bytes(c, res + ri);
		if (ri + MB_MAXBYTES > MAXWLEN)
		    break;
		prevc = c;
	    }
	}
    }
    else
#endif
    {

	for (s = inword; (c = *s) != NUL; ++s)
	{
	    if (vim_iswhite(c))
		c = ' ';
	    else
		c = slang->sl_sal_first[c];
	    if (c != NUL && (ri == 0 || res[ri - 1] != c))
		res[ri++] = c;
	}
    }

    res[ri] = NUL;
}
