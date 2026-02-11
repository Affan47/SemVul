da_refgen(pTHX_ SV *sv) {
	SV *rv;
	PREP_ALIAS_INC(sv);
	rv = sv_newmortal();
	sv_upgrade(rv, SVt_RV);
	SvRV(rv) = sv;
	SvROK_on(rv);
	SvREADONLY_on(rv);
	return rv;
}
