Perl_sv_unref_flags(pTHX_ SV *const ref, const U32 flags)
{
    SV* const target = SvRV(ref);

    PERL_ARGS_ASSERT_SV_UNREF_FLAGS;

    if (SvWEAKREF(ref)) {
    	sv_del_backref(target, ref);
	SvWEAKREF_off(ref);
	SvRV_set(ref, NULL);
	return;
    }
    SvRV_set(ref, NULL);
    SvROK_off(ref);


    if (SvREFCNT(target) != 1 || (flags & SV_IMMEDIATE_UNREF))
	SvREFCNT_dec_NN(target);
    else
	sv_2mortal(target);
}
