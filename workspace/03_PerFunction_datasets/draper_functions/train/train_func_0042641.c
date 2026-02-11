deleteregion(int f, int n)
{
    REGION          region;

    if (curbp->b_mode&MDVIEW)
      return(rdonly());

    if (getregion(&region, curwp->w_markp, curwp->w_marko) == TRUE){
	curwp->w_dotp = region.r_linep;
	curwp->w_doto = region.r_offset;
	curwp->w_markp = NULL;
#ifdef	_WINDOWS
	mswin_allowcopycut(NULL);
#endif
	if(ldelete(region.r_size, NULL)){
	    if(curwp->w_dotp == curwp->w_linep
	       && curwp->w_dotp == curbp->b_linep){
		curwp->w_force = 0;
		curwp->w_flag |= WFFORCE;
	    }

	    return(TRUE);
	}
    }

    return (FALSE);
}
