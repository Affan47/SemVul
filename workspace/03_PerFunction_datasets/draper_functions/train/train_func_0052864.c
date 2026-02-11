Perl_magic_getnkeys(pTHX_ SV *sv, MAGIC *mg)
{
    HV * const hv = MUTABLE_HV(LvTARG(sv));
    I32 i = 0;

    PERL_ARGS_ASSERT_MAGIC_GETNKEYS;
    PERL_UNUSED_ARG(mg);

    if (hv) {
         (void) hv_iterinit(hv);
         if (! SvTIED_mg((const SV *)hv, PERL_MAGIC_tied))
	     i = HvUSEDKEYS(hv);
         else {
	     while (hv_iternext(hv))
	         i++;
         }
    }

    sv_setiv(sv, (IV)i);
    return 0;
}
