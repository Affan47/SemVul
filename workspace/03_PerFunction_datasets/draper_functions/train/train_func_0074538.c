mpickstuff(mtmp, str)
	register struct monst *mtmp;
	register const char *str;
{
	register struct obj *otmp, *otmp2;


	if(mtmp->isshk && inhishop(mtmp)) return FALSE;

	for(otmp = level.objects[mtmp->mx][mtmp->my]; otmp; otmp = otmp2) {
	    otmp2 = otmp->nexthere;

	    if (!str ? searches_for_item(mtmp,otmp) :
		  !!(index(str, otmp->oclass))) {
		if (otmp->otyp == GOOSE_POOP) continue;
		if (otmp->otyp == CORPSE && mtmp->data->mlet != S_NYMPH &&

			!touch_petrifies(&mons[otmp->corpsenm]) &&
			otmp->corpsenm != PM_LIZARD &&
			!acidic(&mons[otmp->corpsenm])) continue;
		if (!touch_artifact(otmp,mtmp)) continue;
		if (!can_carry(mtmp,otmp)) continue;
		if (is_pool(mtmp->mx,mtmp->my)) continue;
#ifdef INVISIBLE_OBJECTS
		if (otmp->oinvis && !perceives(mtmp->data)) continue;
#endif
		if (cansee(mtmp->mx,mtmp->my) && flags.verbose)
			pline("%s picks up %s.", Monnam(mtmp),
			      (distu(mtmp->mx, mtmp->my) <= 5) ?
				doname(otmp) : distant_name(otmp, doname));
		obj_extract_self(otmp);

		if (otmp->otyp == BOULDER)
		    unblock_point(otmp->ox,otmp->oy);
		(void) mpickobj(mtmp, otmp);
		m_dowear(mtmp, FALSE);
		newsym(mtmp->mx, mtmp->my);
		return TRUE;
	    }
	}
	return FALSE;
}
