Perl_require_pv(pTHX_ const char *pv)
{
    dVAR;
    dSP;
    SV* sv;

    PERL_ARGS_ASSERT_REQUIRE_PV;

    PUSHSTACKi(PERLSI_REQUIRE);
    PUTBACK;
    sv = Perl_newSVpvf(aTHX_ "require q%c%s%c", 0, pv, 0);
    eval_sv(sv_2mortal(sv), G_DISCARD);
    SPAGAIN;
    POPSTACK;
}
