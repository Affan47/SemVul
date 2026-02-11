match_suffix(fname)
    char_u	*fname;
{
    int		fnamelen, setsuflen;
    char_u	*setsuf;
#define MAXSUFLEN 30
    char_u	suf_buf[MAXSUFLEN];

    fnamelen = (int)STRLEN(fname);
    setsuflen = 0;
    for (setsuf = p_su; *setsuf; )
    {
	setsuflen = copy_option_part(&setsuf, suf_buf, MAXSUFLEN, ".,");
	if (fnamelen >= setsuflen
		&& fnamencmp(suf_buf, fname + fnamelen - setsuflen,
					      (size_t)setsuflen) == 0)
	    break;
	setsuflen = 0;
    }
    return (setsuflen != 0);
}
