Perl_sv_rvweaken(pTHX_ SV *const sv)
{
    SV *tsv;

    PERL_ARGS_ASSERT_SV_RVWEAKEN;

    if (!SvOK(sv))
	return sv;
    if (!SvROK(sv))
	Perl_croak(aTHX_ "Can't weaken a nonreference");
    else if (SvWEAKREF(sv)) {
	Perl_ck_warner(aTHX_ packWARN(WARN_MISC), "Reference is already weak");
	return sv;
    }
    else if (SvREADONLY(sv)) croak_no_modify();
    tsv = SvRV(sv);
    Perl_sv_add_backref(aTHX_ tsv, sv);
    SvWEAKREF_on(sv);
    SvREFCNT_dec_NN(tsv);
    return sv;
}
