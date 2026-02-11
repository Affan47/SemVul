resurrect()
{
	struct monst *mtmp, **mmtmp;
	long elapsed;
	const char *verb;

	if (!flags.no_of_wizards) {

	    verb = "kill";
	    mtmp = makemon(&mons[PM_WIZZARD_OF_YENDOR], u.ux, u.uy, MM_NOWAIT);
	} else {

	    verb = "elude";
	    mmtmp = &migrating_mons;
	    while ((mtmp = *mmtmp) != 0) {
		if (mtmp->iswiz &&

			!mon_has_amulet(mtmp) &&
			(elapsed = monstermoves - mtmp->mlstmv) > 0L) {
		    mon_catchup_elapsed_time(mtmp, elapsed);
		    if (elapsed >= LARGEST_INT) elapsed = LARGEST_INT - 1;
		    elapsed /= 50L;
		    if (mtmp->msleeping && rn2((int)elapsed + 1))
			mtmp->msleeping = 0;
		    if (mtmp->mfrozen == 1)
			mtmp->mfrozen = 0,  mtmp->mcanmove = 1;
		    if (mtmp->mcanmove && !mtmp->msleeping) {
			*mmtmp = mtmp->nmon;
			mon_arrive(mtmp, TRUE);


			break;
		    }
		}
		mmtmp = &mtmp->nmon;
	    }
	}

	if (mtmp) {
		mtmp->msleeping = mtmp->mtame = mtmp->mpeaceful = 0;
		set_malign(mtmp);
		pline("A voice booms out...");
		verbalize("So thou thought thou couldst %s me, fool.", verb);
	}

}
