PerlIOVia_bufsiz(pTHX_ PerlIO * f)
{
    if (PerlIOBase(f)->flags & PERLIO_F_CANREAD) {
	PerlIOVia *s = PerlIOSelf(f, PerlIOVia);
	if (s->var)
	    return SvCUR(s->var);
    }
    return 0;
}
