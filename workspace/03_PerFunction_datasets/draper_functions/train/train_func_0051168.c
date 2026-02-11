backdel(int f, int n)
{
    register int    s;

    if (curbp->b_mode&MDVIEW)
      return(rdonly());

    if (n < 0)
      return (forwdel(f, -n));

    if(TERM_OPTIMIZE && curwp->w_dotp != curwp->w_bufp->b_linep){
	int l;

	if(worthit(&l) && curwp->w_doto == 0 &&
	   lback(curwp->w_dotp) != curwp->w_bufp->b_linep){
	    if(l == curwp->w_toprow)
	      scrollup(curwp, l+1, 1);
	    else if(llength(lback(curwp->w_dotp)) == 0)
	      scrollup(curwp, l-1, 1);
	    else
	      scrollup(curwp, l, 1);
	}
    }

    if (f != FALSE) {
	if ((lastflag&CFKILL) == 0)
	  kdelete();

	thisflag |= CFKILL;
    }

    if ((s=backchar(f, n)) == TRUE)
      s = ldelete((long) n, f ? kinsert : NULL);

    return (s);
}
