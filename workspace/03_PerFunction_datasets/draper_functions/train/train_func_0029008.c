Perl_sv_pv(pTHX_ SV *sv)
{
    PERL_ARGS_ASSERT_SV_PV;

    if (SvPOK(sv))
        return SvPVX(sv);

    return sv_2pv(sv, NULL);
}
