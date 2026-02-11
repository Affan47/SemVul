PerlIOBase_setlinebuf(pTHX_ PerlIO *f)
{
    PERL_UNUSED_CONTEXT;
    if (PerlIOValid(f)) {
	PerlIOBase(f)->flags |= PERLIO_F_LINEBUF;
    }
}
