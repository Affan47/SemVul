da_fetch(pTHX_ SV *a1, SV *a2) {
	switch ((Size_t) a1) {
	case DA_ALIAS_PAD:
		return PL_curpad[(Size_t) a2];
	case DA_ALIAS_RV:
		if (SvTYPE(a2) == SVt_PVGV)
			a2 = GvSV(a2);
		else if (!SvROK(a2) || !(a2 = SvRV(a2))
			|| (SvTYPE(a2) > SVt_PVLV && SvTYPE(a2) != SVt_PVGV))
			Perl_croak(aTHX_ "Not a SCALAR reference");
	case DA_ALIAS_GV:
		return a2;
	case DA_ALIAS_AV:
	case DA_ALIAS_HV:
		break;
	default:
		switch (SvTYPE(a1)) {
			SV **svp;
			HE *he;
		case SVt_PVAV:
			svp = av_fetch((AV *) a1, (Size_t) a2, FALSE);
			return svp ? *svp : &PL_sv_undef;
		case SVt_PVHV:
			he = hv_fetch_ent((HV *) a1, a2, FALSE, 0);
			return he ? HeVAL(he) : &PL_sv_undef;
		default:
			 ;
		}
	}
	Perl_croak(aTHX_ DA_TARGET_ERR);
	return NULL;
}
