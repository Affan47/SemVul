solver_verify_sip_wcs(solver_t* solver, sip_t* sip) {
    int i, nindexes;
    MatchObj mo;
	MatchObj* pmo;
	anbool olddqb;

	pmo = &mo;

	if (!solver->vf)
		solver_preprocess_field(solver);


    set_matchobj_template(solver, pmo);
    memcpy(&(mo.wcstan), &(sip->wcstan), sizeof(tan_t));
    mo.wcs_valid = TRUE;
    mo.scale = sip_pixel_scale(sip);
    set_center_and_radius(solver, pmo, NULL, sip);
	olddqb = solver->distance_from_quad_bonus;
	solver->distance_from_quad_bonus = FALSE;

    nindexes = pl_size(solver->indexes);
    for (i=0; i<nindexes; i++) {
        index_t* index = pl_get(solver->indexes, i);
        set_index(solver, index);
        solver_inject_match(solver, pmo, sip);
    }


	solver->distance_from_quad_bonus = olddqb;
}
