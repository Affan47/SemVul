rloc_to(mtmp, x, y)
struct monst *mtmp;
register int x, y;
{
	register int oldx = mtmp->mx, oldy = mtmp->my;
	boolean resident_shk = mtmp->isshk && inhishop(mtmp);

	if (x == mtmp->mx && y == mtmp->my)
		return;

	if (oldx) {
	    if (mtmp->wormno)
		remove_worm(mtmp);
	    else {
		remove_monster(oldx, oldy);
		newsym(oldx, oldy);
	    }
	}

	place_monster(mtmp, x, y);
	update_monster_region(mtmp);

	if (mtmp->wormno)
		place_worm_tail_randomly(mtmp, x, y);

	if (u.ustuck == mtmp) {
		if (u.uswallow) {
			u.ux = x;
			u.uy = y;
			docrt();
		} else	u.ustuck = 0;
	}

	newsym(x, y);
	set_apparxy(mtmp);


	if (resident_shk && !inhishop(mtmp)) make_angry_shk(mtmp, oldx, oldy);
}
