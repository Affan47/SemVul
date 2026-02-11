foldlevelMarker(flp)
    fline_T	*flp;
{
    char_u	*startmarker;
    int		cstart;
    int		cend;
    int		start_lvl = flp->lvl;
    char_u	*s;
    int		n;


    startmarker = flp->wp->w_p_fmr;
    cstart = *startmarker;
    ++startmarker;
    cend = *foldendmarker;


    flp->start = 0;
    flp->lvl_next = flp->lvl;

    s = ml_get_buf(flp->wp->w_buffer, flp->lnum + flp->off, FALSE);
    while (*s)
    {
	if (*s == cstart
		  && STRNCMP(s + 1, startmarker, foldstartmarkerlen - 1) == 0)
	{

	    s += foldstartmarkerlen;
	    if (VIM_ISDIGIT(*s))
	    {
		n = atoi((char *)s);
		if (n > 0)
		{
		    flp->lvl = n;
		    flp->lvl_next = n;
		    if (n <= start_lvl)
			flp->start = 1;
		    else
			flp->start = n - start_lvl;
		}
	    }
	    else
	    {
		++flp->lvl;
		++flp->lvl_next;
		++flp->start;
	    }
	}
	else if (*s == cend
	      && STRNCMP(s + 1, foldendmarker + 1, foldendmarkerlen - 1) == 0)
	{

	    s += foldendmarkerlen;
	    if (VIM_ISDIGIT(*s))
	    {
		n = atoi((char *)s);
		if (n > 0)
		{
		    flp->lvl = n;
		    flp->lvl_next = n - 1;

		    if (flp->lvl_next > flp->lvl)
			flp->lvl_next = flp->lvl;
		}
	    }
	    else
		--flp->lvl_next;
	}
	else
	    mb_ptr_adv(s);
    }


    if (flp->lvl_next < 0)
	flp->lvl_next = 0;
}
