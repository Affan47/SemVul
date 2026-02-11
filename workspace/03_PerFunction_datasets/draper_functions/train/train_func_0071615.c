PerlIOVia_tell(pTHX_ PerlIO * f)
{
    PerlIOVia *s = PerlIOSelf(f, PerlIOVia);
    SV *result =
	PerlIOVia_method(aTHX_ f, MYMethod(TELL), G_SCALAR, Nullsv);
    return (result)
	   ? (SvNOK(result) ? (Off_t)SvNV(result) : (Off_t)SvIV(result))
	   : (Off_t) - 1;
}
