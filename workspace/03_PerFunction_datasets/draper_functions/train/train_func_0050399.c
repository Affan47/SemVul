dochugw(mtmp)
	register struct monst *mtmp;
{
	register int x = mtmp->mx, y = mtmp->my;
	boolean already_saw_mon = !occupation ? 0 : canspotmon(mtmp);
	int rd = dochug(mtmp);
#if 0

	int dd;

	if(Warning && !rd && !mtmp->mpeaceful &&
			(dd = distu(mtmp->mx,mtmp->my)) < distu(x,y) &&
			dd < 100 && !canseemon(mtmp)) {


	    if (spec_ability(uwep, SPFX_WARN) && spec_dbon(uwep, mtmp, 1))
		warnlevel = 100;
	    else if ((int) (mtmp->m_lev / 4) > warnlevel)
		warnlevel = (mtmp->m_lev / 4);
	}
#endif


	if (occupation && !rd && !Confusion &&
	    (!mtmp->mpeaceful || Hallucination) &&

	    distu(mtmp->mx,mtmp->my) <= (BOLT_LIM+1)*(BOLT_LIM+1) &&

	    (!already_saw_mon || !couldsee(x,y) ||
		distu(x,y) > (BOLT_LIM+1)*(BOLT_LIM+1)) &&

	    (canseemon(mtmp) ||
		(sensemon(mtmp) && couldsee(mtmp->mx,mtmp->my))) &&
	    mtmp->mcanmove &&
	    !noattacks(mtmp->data) && !onscary(u.ux, u.uy, mtmp))
		stop_occupation();

	return(rd);
}
