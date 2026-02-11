Perl_report_uninit(pTHX_ const SV *uninit_sv)
{
    dVAR;
    if (PL_op) {
	SV* varname = NULL;
	if (uninit_sv && PL_curpad) {
	    varname = find_uninit_var(PL_op, uninit_sv,0);
	    if (varname)
		sv_insert(varname, 0, 0, " ", 1);
	}

	Perl_warner(aTHX_ packWARN(WARN_UNINITIALIZED), PL_warn_uninit_sv,
		SVfARG(varname ? varname : &PL_sv_no),
		" in ", OP_DESC(PL_op));
    }
    else
	Perl_warner(aTHX_ packWARN(WARN_UNINITIALIZED), PL_warn_uninit,
		    "", "", "");
}
