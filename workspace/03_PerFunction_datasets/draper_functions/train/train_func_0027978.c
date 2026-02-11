modperl_perl_do_sprintf(pTHX_ SV *sv, I32 len, SV **sarg)
{
    STRLEN patlen;
    char *pat = SvPV(*sarg, patlen);
    bool do_taint = FALSE;

    sv_vsetpvfn(sv, pat, patlen, (va_list *)NULL, sarg + 1, len - 1, &do_taint);
    SvSETMAGIC(sv);
    if (do_taint) {
        SvTAINTED_on(sv);
    }
}
