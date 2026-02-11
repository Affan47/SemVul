Perl_sv_does_sv(pTHX_ SV *sv, SV *namesv, U32 flags)
{
    SV *classname;
    bool does_it;
    SV *methodname;
    dSP;

    PERL_ARGS_ASSERT_SV_DOES_SV;
    PERL_UNUSED_ARG(flags);

    ENTER;
    SAVETMPS;

    SvGETMAGIC(sv);

    if (!SvOK(sv) || !(SvROK(sv) || (SvPOK(sv) && SvCUR(sv)))) {
	LEAVE;
	return FALSE;
    }

    if (sv_isobject(sv)) {
	classname = sv_ref(NULL,SvRV(sv),TRUE);
    } else {
	classname = sv;
    }

    if (sv_eq(classname, namesv)) {
	LEAVE;
	return TRUE;
    }

    PUSHMARK(SP);
    EXTEND(SP, 2);
    PUSHs(sv);
    PUSHs(namesv);
    PUTBACK;

    methodname = newSVpvs_flags("isa", SVs_TEMP);


    SvSCREAM_on(methodname);
    call_sv(methodname, G_SCALAR | G_METHOD);
    SPAGAIN;

    does_it = SvTRUE( TOPs );
    FREETMPS;
    LEAVE;

    return does_it;
}
