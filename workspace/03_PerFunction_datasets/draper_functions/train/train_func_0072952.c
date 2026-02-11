PerlIOVia_get_cnt(pTHX_ PerlIO * f)
{
    if (PerlIOBase(f)->flags & PERLIO_F_CANREAD) {
	PerlIOVia *s = PerlIOSelf(f, PerlIOVia);
	if (s->var) {
	    return s->cnt;
	}
    }
    return 0;
}
