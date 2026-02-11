DataAlias_pp_andassign(pTHX) {
	dSP;
	SV *a2 = POPs;
	SV *sv = da_fetch(aTHX_ TOPs, a2);
	if (SvTRUE(sv)) {

		return cLOGOP->op_other;
	}
	SETs(sv);
	RETURN;
}
