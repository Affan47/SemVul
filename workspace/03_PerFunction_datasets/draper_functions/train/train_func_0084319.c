lnewline(void)
{
    register CELL   *cp1;
    register CELL   *cp2;
    register LINE   *lp1;
    register LINE   *lp2;
    register int    doto;
    register WINDOW *wp;

    if (curbp->b_mode&MDVIEW)
      return(rdonly());

    lchange(WFHARD);
    lp1  = curwp->w_dotp;
    doto = curwp->w_doto;
    if ((lp2=lalloc(doto)) == NULL)
      return (FALSE);

    cp1 = &lp1->l_text[0];
    cp2 = &lp2->l_text[0];
    while (cp1 != &lp1->l_text[doto])
      *cp2++ = *cp1++;

    cp2 = &lp1->l_text[0];
    while (cp1 != &lp1->l_text[lp1->l_used])
      *cp2++ = *cp1++;

    lp1->l_used -= doto;
    lp2->l_bp = lp1->l_bp;
    lp1->l_bp = lp2;
    lp2->l_bp->l_fp = lp2;
    lp2->l_fp = lp1;
    wp = wheadp;
    while (wp != NULL) {
	if (wp->w_linep == lp1)
	  wp->w_linep = lp2;

	if (wp->w_dotp == lp1) {
	    if (wp->w_doto < doto)
	      wp->w_dotp = lp2;
	    else
	      wp->w_doto -= doto;
	}

	if (wp->w_imarkp == lp1) {
	    if (wp->w_imarko < doto)
	      wp->w_imarkp = lp2;
	    else
	      wp->w_imarko -= doto;
	}

	if (wp->w_markp == lp1) {
	    if (wp->w_marko < doto)
	      wp->w_markp = lp2;
	    else
	      wp->w_marko -= doto;
	}
	wp = wp->w_wndp;
    }


    ++curbp->b_linecnt;
    return (TRUE);
}
