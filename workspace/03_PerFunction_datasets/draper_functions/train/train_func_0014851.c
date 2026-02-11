mlevel_tele_trap(mtmp, trap, force_it, in_sight)
struct monst *mtmp;
struct trap *trap;
boolean force_it;
int in_sight;
{
	int tt = trap->ttyp;
	struct permonst *mptr = mtmp->data;

	if (mtmp == u.ustuck)
	    return 0;
	if (teleport_pet(mtmp, force_it)) {
	    d_level tolevel;
	    int migrate_typ = MIGR_RANDOM;

	    if ((tt == HOLE || tt == TRAPDOOR)) {
		if (Is_stronghold(&u.uz)) {
		    assign_level(&tolevel, &valley_level);
		} else if (Is_botlevel(&u.uz)) {
		    if (in_sight && trap->tseen)
			pline("%s avoids the %s.", Monnam(mtmp),
			(tt == HOLE) ? "hole" : "trap");
		    return 0;
		} else {
		    get_level(&tolevel, depth(&u.uz) + 1);
		}
	    } else if (tt == MAGIC_PORTAL) {
		if (In_endgame(&u.uz) &&
		    (mon_has_amulet(mtmp) || is_home_elemental(mptr))) {
		    if (in_sight && mptr->mlet != S_ELEMENTAL) {
			pline("%s seems to shimmer for a moment.",
							Monnam(mtmp));
			seetrap(trap);
		    }
		    return 0;
		} else {
		    assign_level(&tolevel, &trap->dst);
		    migrate_typ = MIGR_PORTAL;
		}
	    } else {
		int nlev;

		if (mon_has_amulet(mtmp) || In_endgame(&u.uz)) {
		    if (in_sight)
			pline("%s seems very disoriented for a moment.",
				Monnam(mtmp));
		    return 0;
		}
		nlev = random_teleport_level();
		if (nlev == depth(&u.uz)) {
		    if (in_sight)
			pline("%s shudders for a moment.", Monnam(mtmp));
		    return 0;
		}
		get_level(&tolevel, nlev);
	    }

	    if (in_sight) {
		pline("Suddenly, %s disappears out of sight.", mon_nam(mtmp));
		seetrap(trap);
	    }
	    migrate_to_level(mtmp, ledger_no(&tolevel),
			     migrate_typ, (coord *)0);
	    return 3;
	}
	return 0;
}
