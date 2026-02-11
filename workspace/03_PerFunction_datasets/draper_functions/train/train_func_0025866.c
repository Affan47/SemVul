foldtext_cleanup(str)
    char_u	*str;
{
    char_u	*cms_start;
    int		cms_slen = 0;
    char_u	*cms_end;
    int		cms_elen = 0;
    char_u	*s;
    char_u	*p;
    int		len;
    int		did1 = FALSE;
    int		did2 = FALSE;


    cms_start = skipwhite(curbuf->b_p_cms);
    cms_slen = (int)STRLEN(cms_start);
    while (cms_slen > 0 && vim_iswhite(cms_start[cms_slen - 1]))
	--cms_slen;


    cms_end = (char_u *)strstr((char *)cms_start, "%s");
    if (cms_end != NULL)
    {
	cms_elen = cms_slen - (int)(cms_end - cms_start);
	cms_slen = (int)(cms_end - cms_start);


	while (cms_slen > 0 && vim_iswhite(cms_start[cms_slen - 1]))
	    --cms_slen;


	s = skipwhite(cms_end + 2);
	cms_elen -= (int)(s - cms_end);
	cms_end = s;
    }
    parseMarker(curwin);

    for (s = str; *s != NUL; )
    {
	len = 0;
	if (STRNCMP(s, curwin->w_p_fmr, foldstartmarkerlen) == 0)
	    len = foldstartmarkerlen;
	else if (STRNCMP(s, foldendmarker, foldendmarkerlen) == 0)
	    len = foldendmarkerlen;
	if (len > 0)
	{
	    if (VIM_ISDIGIT(s[len]))
		++len;


	    for (p = s; p > str && vim_iswhite(p[-1]); --p)
		;
	    if (p >= str + cms_slen
			   && STRNCMP(p - cms_slen, cms_start, cms_slen) == 0)
	    {
		len += (int)(s - p) + cms_slen;
		s = p - cms_slen;
	    }
	}
	else if (cms_end != NULL)
	{
	    if (!did1 && cms_slen > 0 && STRNCMP(s, cms_start, cms_slen) == 0)
	    {
		len = cms_slen;
		did1 = TRUE;
	    }
	    else if (!did2 && cms_elen > 0
					&& STRNCMP(s, cms_end, cms_elen) == 0)
	    {
		len = cms_elen;
		did2 = TRUE;
	    }
	}
	if (len != 0)
	{
	    while (vim_iswhite(s[len]))
		++len;
	    STRMOVE(s, s + len);
	}
	else
	{
	    mb_ptr_adv(s);
	}
    }
}
