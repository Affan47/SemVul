PerlIOBuf_read(pTHX_ PerlIO *f, void *vbuf, Size_t count)
{
    if (PerlIOValid(f)) {
        const PerlIOBuf * const b = PerlIOSelf(f, PerlIOBuf);
	if (!b->ptr)
	    PerlIO_get_base(f);
	return PerlIOBase_read(aTHX_ f, vbuf, count);
    }
    return 0;
}
