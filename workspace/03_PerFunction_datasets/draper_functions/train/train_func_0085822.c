S_magic_methcall1(pTHX_ SV *sv, const MAGIC *mg, const char *meth, U32 flags,
    int n, SV *val)
{
    dVAR;
    SV* arg1 = NULL;

    PERL_ARGS_ASSERT_MAGIC_METHCALL1;

    if (mg->mg_ptr) {
	if (mg->mg_len >= 0) {
	    arg1 = newSVpvn_flags(mg->mg_ptr, mg->mg_len, SVs_TEMP);
	}
	else if (mg->mg_len == HEf_SVKEY)
	    arg1 = MUTABLE_SV(mg->mg_ptr);
    }
    else if (mg->mg_type == PERL_MAGIC_tiedelem) {
	arg1 = newSViv((IV)(mg->mg_len));
	sv_2mortal(arg1);
    }
    if (!arg1) {
	return Perl_magic_methcall(aTHX_ sv, mg, meth, flags, n - 1, val);
    }
    return Perl_magic_methcall(aTHX_ sv, mg, meth, flags, n, arg1, val);
}
