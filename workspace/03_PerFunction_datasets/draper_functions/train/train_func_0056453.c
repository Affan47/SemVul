slept_monst(mon)
struct monst *mon;
{
	if ((mon->msleeping || !mon->mcanmove) && mon == u.ustuck &&
		!sticks(youmonst.data) && !u.uswallow) {
	    pline("%s grip relaxes.", s_suffix(Monnam(mon)));
	    unstuck(mon);
	}
}
