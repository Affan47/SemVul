record_match_callback(MatchObj* mo, void* userdata) {
	blind_t* bp = userdata;
	solver_t* sp = &(bp->solver);
    MatchObj* mymo;
    int ind;

	check_time_limits(bp);


    ind = bl_insert_sorted(bp->solutions, mo, compare_matchobjs);
    mymo = bl_access(bp->solutions, ind);


	mo->theta = NULL;
	mo->matchodds = NULL;
	mo->refxyz = NULL;
	mo->refxy = NULL;
	mo->refstarid = NULL;
	mo->testperm = NULL;


    if (bp->indexrdlsfname || bp->scamp_fname || bp->corr_fname) {
		int i;


		if (bp->sort_rdls) {
			if (sort_rdls(mymo, bp)) {
				ERROR("Failed to sort RDLS file by column \"%s\"", bp->sort_rdls);
			}
		}

		logdebug("Converting %i reference stars from xyz to radec\n", mymo->nindex);
		mymo->refradec = malloc(mymo->nindex * 2 * sizeof(double));
		for (i=0; i<mymo->nindex; i++) {
			xyzarr2radecdegarr(mymo->refxyz+i*3, mymo->refradec+i*2);
			logdebug("  %i: radec %.2f,%.2f\n", i, mymo->refradec[i*2], mymo->refradec[i*2+1]);
		}

		mymo->fieldxy = malloc(mymo->nfield * 2 * sizeof(double));

		memcpy(mymo->fieldxy, bp->solver.vf->xy, mymo->nfield * 2 * sizeof(double));


		if (bp->rdls_tagalong || bp->rdls_tagalong_all)
			grab_tagalong_data(sp->index->starkd, mymo, bp, mymo->refstarid, mymo->nindex);


		assert(bp->xyls_tagalong_all);
		assert(!bp->xyls_tagalong);
		if (bp->xyls_tagalong_all)
			grab_field_tagalong_data(mymo, bp->xyls, mymo->nfield);
	}

	if (mymo->logodds < bp->logratio_tosolve)
		return FALSE;


    bp->nsolves_sofar++;
    if (bp->nsolves_sofar < bp->nsolves) {
        logmsg("Found a quad that solves the image; that makes %i of %i required.\n",
               bp->nsolves_sofar, bp->nsolves);
	} else {
        if (bp->solver.index) {
			char* base = basename_safe(bp->solver.index->indexname);
            logmsg("Field %i: solved with index %s.\n", mymo->fieldnum, base);
            free(base);
        } else {
            logmsg("Field %i: solved with index %i", mymo->fieldnum, mymo->indexid);
            if (mymo->healpix >= 0)
                logmsg(", healpix %i\n", mymo->healpix);
            else
                logmsg("\n");
        }
        return TRUE;
    }
	return FALSE;
}
