extractHChans (maze* mp)
{
    int i;
    snode* np;
    Dt_t* hchans = dtopen (&chanItemDisc, Dtoset);

    for (i = 0; i < mp->ncells; i++) {
	channel* chp;
	cell* cp = mp->cells+i;
	cell* nextcp;
	if (IsHScan(cp)) continue;


	while ((np = cp->sides[M_LEFT]) && (nextcp = np->cells[0]) &&
	    !IsNode(nextcp)) {
	    cp = nextcp;
	}

	chp = NEW(channel);
	chp->cp = cp;
	chp->p.p1 = cp->bb.LL.x;


	cp->flags |= MZ_HSCAN;
	while ((np = cp->sides[M_RIGHT]) && (nextcp = np->cells[1]) &&
	    !IsNode(nextcp)) {
	    cp = nextcp;
	    cp->flags |= MZ_HSCAN;
	}

        chp->p.p2 = cp->bb.UR.x;
	addChan (hchans, chp, chp->cp->bb.LL.y);
    }
    return hchans;
}
