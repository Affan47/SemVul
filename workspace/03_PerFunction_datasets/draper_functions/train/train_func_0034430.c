S_sv_unglob(pTHX_ SV *const sv, U32 flags)
{
    dVAR;
    void *xpvmg;
    HV *stash;
    SV * const temp = flags & SV_COW_DROP_PV ? NULL : sv_newmortal();

    PERL_ARGS_ASSERT_SV_UNGLOB;

    assert(SvTYPE(sv) == SVt_PVGV || SvTYPE(sv) == SVt_PVLV);
    SvFAKE_off(sv);
    if (!(flags & SV_COW_DROP_PV))
	gv_efullname3(temp, MUTABLE_GV(sv), "*");

    if (GvGP(sv)) {
        if(GvCVu((const GV *)sv) && (stash = GvSTASH(MUTABLE_GV(sv)))
	   && HvNAME_get(stash))
            mro_method_changed_in(stash);
	gp_free(MUTABLE_GV(sv));
    }
    if (GvSTASH(sv)) {
	sv_del_backref(MUTABLE_SV(GvSTASH(sv)), sv);
	GvSTASH(sv) = NULL;
    }
    GvMULTI_off(sv);
    if (GvNAME_HEK(sv)) {
	unshare_hek(GvNAME_HEK(sv));
    }
    isGV_with_GP_off(sv);

    if(SvTYPE(sv) == SVt_PVGV) {

	xpvmg = new_XPVMG();
	StructCopy(SvANY(sv), xpvmg, XPVMG);
	del_XPVGV(SvANY(sv));
	SvANY(sv) = xpvmg;

	SvFLAGS(sv) &= ~SVTYPEMASK;
	SvFLAGS(sv) |= SVt_PVMG;
    }


    if (flags & SV_COW_DROP_PV) SvOK_off(sv);
    else sv_setsv_flags(sv, temp, 0);

    if ((const GV *)sv == PL_last_in_gv)
	PL_last_in_gv = NULL;
    else if ((const GV *)sv == PL_statgv)
	PL_statgv = NULL;
}
