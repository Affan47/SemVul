resists_drli(mon)
struct monst *mon;
{
	struct permonst *ptr = mon->data;
	struct obj *wep = ((mon == &youmonst) ? uwep : MON_WEP(mon));

	return (boolean)(is_undead(ptr) || is_demon(ptr) || is_were(ptr) ||
			 ptr == &mons[PM_DEATH] ||
			 (wep && wep->oartifact && defends(AD_DRLI, wep)));
}
