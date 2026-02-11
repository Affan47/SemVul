combine_two_entries (hdrp, oldp, newp)
    struct dent *	hdrp;
    register struct dent *
			oldp;
    register struct dent *
			newp;
    {

    if (acoversb (oldp, newp))
	{

	combineaffixes (oldp, newp);
	oldp->flagfield |= (newp->flagfield & KEEP);
	hdrp->flagfield |= (newp->flagfield & KEEP);
	myfree (newp->word);
	return 1;
	}
    else if (acoversb (newp, oldp))
	{


	combineaffixes (newp, oldp);
	newp->flagfield |= (oldp->flagfield & (KEEP | MOREVARIANTS));
	hdrp->flagfield |= (newp->flagfield & KEEP);
	newp->next = oldp->next;


	if (oldp->word != NULL)
	    (void) strcpy ((char *) oldp->word, (char *) newp->word);
	myfree (newp->word);
	newp->word = oldp->word;
	*oldp = *newp;

	if (captype (newp->flagfield) == FOLLOWCASE
	  &&  (hdrp->flagfield & (CAPTYPEMASK | MOREVARIANTS))
	    != (ALLCAPS | MOREVARIANTS))
	    (void) addvheader (hdrp);
	return 1;
	}
    else
	return 0;
    }
