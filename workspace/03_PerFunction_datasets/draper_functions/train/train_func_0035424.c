shkcatch(obj, x, y)
register struct obj *obj;
register xchar x, y;
{
	register struct monst *shkp;

	if (!(shkp = shop_keeper(inside_shop(x, y))) ||
	    !inhishop(shkp)) return(0);

	if (shkp->mcanmove && !shkp->msleeping &&
	    (*u.ushops != ESHK(shkp)->shoproom || !inside_shop(u.ux, u.uy)) &&
	    dist2(shkp->mx, shkp->my, x, y) < 3 &&

	    (shkp->mx != x || shkp->my != y)) {
		if (mnearto(shkp, x, y, TRUE))
		    verbalize("Out of my way, scum!");
		if (cansee(x, y)) {
		    pline("%s nimbly%s catches %s.",
			  Monnam(shkp),
			  (x == shkp->mx && y == shkp->my) ? "" : " reaches over and",
			  the(xname(obj)));
		    if (!canspotmon(shkp))
			map_invisible(x, y);
		    delay_output();
		    mark_synch();
		}
		subfrombill(obj, shkp);
		(void) mpickobj(shkp, obj);
		return shkp;
	}
	return (struct monst *)0;
}
