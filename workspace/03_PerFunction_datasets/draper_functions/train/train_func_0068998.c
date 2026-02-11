PerlIOScalar_arg(pTHX_ PerlIO * f, CLONE_PARAMS * param, int flags)
{
    PerlIOScalar *s = PerlIOSelf(f, PerlIOScalar);
    SV *var = s->var;
    if (flags & PERLIO_DUP_CLONE)
	var = PerlIO_sv_dup(aTHX_ var, param);
    else if (flags & PERLIO_DUP_FD) {

	var = newSVsv(var);
    }
    else {
	var = SvREFCNT_inc(var);
    }
    return newRV_noinc(var);
}
