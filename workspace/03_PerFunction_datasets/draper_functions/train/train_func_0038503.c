PerlIOVia_popped(pTHX_ PerlIO * f)
{
    PerlIOVia *s = PerlIOSelf(f, PerlIOVia);
    PerlIOVia_method(aTHX_ f, MYMethod(POPPED), G_VOID, Nullsv);
    if (s->var) {
	SvREFCNT_dec(s->var);
	s->var = Nullsv;
    }

    if (s->io) {
	IoIFP(s->io) = NULL;
	IoOFP(s->io) = NULL;
    }
    if (s->fh) {
	SvREFCNT_dec(s->fh);
	s->fh = Nullsv;
	s->io = NULL;
    }
    if (s->obj) {
	SvREFCNT_dec(s->obj);
	s->obj = Nullsv;
    }
    return 0;
}
