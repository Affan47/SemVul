const_sv_xsub(pTHX_ CV* cv)
{
    dVAR;
    dXSARGS;
    SV *const sv = MUTABLE_SV(XSANY.any_ptr);
    if (items != 0) {
	NOOP;
#if 0

        Perl_croak(aTHX_ "usage: %s::%s()",
                   HvNAME_get(GvSTASH(CvGV(cv))), GvNAME(CvGV(cv)));
#endif
    }
    if (!sv) {
	XSRETURN(0);
    }
    EXTEND(sp, 1);
    ST(0) = sv;
    XSRETURN(1);
}
