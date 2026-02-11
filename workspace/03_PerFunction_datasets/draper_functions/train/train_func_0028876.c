forcevheader (hdrp, oldp, newp)
    register struct dent *	hdrp;
    struct dent *		oldp;
    struct dent *		newp;
    {

    if ((hdrp->flagfield & (CAPTYPEMASK | MOREVARIANTS)) == ALLCAPS
      &&  ((oldp->flagfield ^ newp->flagfield) & KEEP) == 0)
	return;
    else if ((hdrp->flagfield & (CAPTYPEMASK | MOREVARIANTS))
      != (ALLCAPS | MOREVARIANTS))
	(void) addvheader (hdrp);
    }
