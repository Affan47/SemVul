PerlIOMmap_unmap(pTHX_ PerlIO *f)
{
    PerlIOMmap * const m = PerlIOSelf(f, PerlIOMmap);
    IV code = 0;
    if (m->len) {
	PerlIOBuf * const b = &m->base;
	if (b->buf) {


	    code = munmap((char*)m->mptr, m->len);
	    b->buf = NULL;
	    m->len = 0;
	    m->mptr = NULL;
	    if (PerlIO_seek(PerlIONext(f), b->posn, SEEK_SET) != 0)
		code = -1;
	}
	b->ptr = b->end = b->buf;
	PerlIOBase(f)->flags &= ~(PERLIO_F_RDBUF | PERLIO_F_WRBUF);
    }
    return code;
}
