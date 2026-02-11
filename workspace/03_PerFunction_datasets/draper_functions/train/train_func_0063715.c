tactics(mtmp)
	register struct monst *mtmp;
{
	long strat = strategy(mtmp);

	mtmp->mstrategy = (mtmp->mstrategy & STRAT_WAITMASK) | strat;

	switch (strat) {
	    case STRAT_HEAL:


		mtmp->mavenge = 1;
		if (In_W_tower(mtmp->mx, mtmp->my, &u.uz) ||
			(mtmp->iswiz && !xupstair && !mon_has_amulet(mtmp))) {
		    if (!rn2(3 + mtmp->mhp/10)) (void) rloc(mtmp, FALSE);
		} else if (xupstair &&
			 (mtmp->mx != xupstair || mtmp->my != yupstair)) {
		    (void) mnearto(mtmp, xupstair, yupstair, TRUE);
		}

		if (distu(mtmp->mx,mtmp->my) > (BOLT_LIM * BOLT_LIM))
		    if(mtmp->mhp <= mtmp->mhpmax - 8) {
			mtmp->mhp += rnd(8);
			return(1);
		    }


	    case STRAT_NONE:
		if (!rn2(!mtmp->mflee ? 5 : 33)) mnexto(mtmp);
		return(0);

	    default:
	    {
		long  where = (strat & STRAT_STRATMASK);
		xchar tx = STRAT_GOALX(strat),
		      ty = STRAT_GOALY(strat);
		int   targ = strat & STRAT_GOAL;
		struct obj *otmp;

		if(!targ) {
		    return(0);
		}
		if((u.ux == tx && u.uy == ty) || where == STRAT_PLAYER) {

		    mnexto(mtmp);
		    return(0);
		}
		if(where == STRAT_GROUND) {
		    if(!MON_AT(tx, ty) || (mtmp->mx == tx && mtmp->my == ty)) {

			rloc_to(mtmp, tx, ty);

			if ((otmp = on_ground(which_arti(targ))) != 0) {
			    if (cansee(mtmp->mx, mtmp->my))
				pline("%s picks up %s.",
				    Monnam(mtmp),
				    (distu(mtmp->mx, mtmp->my) <= 5) ?
				     doname(otmp) : distant_name(otmp, doname));
			    obj_extract_self(otmp);
			    (void) mpickobj(mtmp, otmp);
			    return(1);
			} else return(0);
		    } else {

			if (!rn2(5)) mnexto(mtmp);
			return(0);
		    }
	        } else {
		    (void) mnearto(mtmp, tx, ty, FALSE);
		    return(0);
		}
	    }
	}

	return(0);
}
