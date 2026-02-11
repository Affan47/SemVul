Perl_av_shift(pTHX_ AV *av)
{
    dVAR;
    SV *retval;
    MAGIC* mg;

    PERL_ARGS_ASSERT_AV_SHIFT;
    assert(SvTYPE(av) == SVt_PVAV);

    if (SvREADONLY(av))
	Perl_croak_no_modify();
    if ((mg = SvTIED_mg((const SV *)av, PERL_MAGIC_tied))) {
	retval = Perl_magic_methcall(aTHX_ MUTABLE_SV(av), mg, "SHIFT", 0, 0);
	if (retval)
	    retval = newSVsv(retval);
	return retval;
    }
    if (AvFILL(av) < 0)
      return &PL_sv_undef;
    retval = *AvARRAY(av);
    if (AvREAL(av))
	*AvARRAY(av) = &PL_sv_undef;
    AvARRAY(av) = AvARRAY(av) + 1;
    AvMAX(av)--;
    AvFILLp(av)--;
    if (SvSMAGICAL(av))
	mg_set(MUTABLE_SV(av));
    return retval;
}
