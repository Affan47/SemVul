S_refto(pTHX_ SV *sv)
{
    dVAR;
    SV* rv;

    PERL_ARGS_ASSERT_REFTO;

    if (SvTYPE(sv) == SVt_PVLV && LvTYPE(sv) == 'y') {
	if (LvTARGLEN(sv))
	    vivify_defelem(sv);
	if (!(sv = LvTARG(sv)))
	    sv = &PL_sv_undef;
	else
	    SvREFCNT_inc_void_NN(sv);
    }
    else if (SvTYPE(sv) == SVt_PVAV) {
	if (!AvREAL((const AV *)sv) && AvREIFY((const AV *)sv))
	    av_reify(MUTABLE_AV(sv));
	SvTEMP_off(sv);
	SvREFCNT_inc_void_NN(sv);
    }
    else if (SvPADTMP(sv) && !IS_PADGV(sv))
        sv = newSVsv(sv);
    else {
	SvTEMP_off(sv);
	SvREFCNT_inc_void_NN(sv);
    }
    rv = sv_newmortal();
    sv_upgrade(rv, SVt_IV);
    SvRV_set(rv, sv);
    SvROK_on(rv);
    return rv;
}
