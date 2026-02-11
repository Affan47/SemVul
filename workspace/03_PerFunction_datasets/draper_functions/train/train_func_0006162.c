DataAlias_pp_helem(pTHX) {
	dSP;
	SV *key = POPs;
	HV *hv = (HV *) POPs;
	HE *he;
	if (SvRMAGICAL(hv) && da_badmagic(aTHX_ (SV *) hv))
		DIE(aTHX_ DA_TIED_ERR, "put", "into", "hash");
	if (SvTYPE(hv) == SVt_PVHV) {
		if (!(he = hv_fetch_ent(hv, key, TRUE, 0)))
			DIE(aTHX_ PL_no_helem, SvPV_nolen(key));
		if (PL_op->op_private & OPpLVAL_INTRO)
			save_helem(hv, key, &HeVAL(he));
	}
#if DA_FEATURE_AVHV
	else if (SvTYPE(hv) == SVt_PVAV && avhv_keys((AV *) hv)) {
		I32 i = da_avhv_index(aTHX_ (AV *) hv, key);
		if (PL_op->op_private & OPpLVAL_INTRO)
			save_aelem((AV *) hv, i, &AvARRAY(hv)[i]);
		key = (SV *) (Size_t) i;
	}
#endif
	else {
		hv = (HV *) &PL_sv_undef;
		key = NULL;
	}
	PUSHaa(hv, key);
	RETURN;
}
