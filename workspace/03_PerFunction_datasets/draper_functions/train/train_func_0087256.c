Perl_hv_placeholders_get(pTHX_ const HV *hv)
{
    dVAR;
    MAGIC * const mg = mg_find((const SV *)hv, PERL_MAGIC_rhash);

    PERL_ARGS_ASSERT_HV_PLACEHOLDERS_GET;

    return mg ? mg->mg_len : 0;
}
