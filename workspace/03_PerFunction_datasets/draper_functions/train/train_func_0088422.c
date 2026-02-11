sdbm_internal_chkpage(const char *pag)
{
	unsigned n;
	unsigned off;
	const unsigned short *ino = (const unsigned short *) pag;


	STATIC_ASSERT(DBM_PBLKSIZ < 0x8000);


	if G_UNLIKELY((n = ino[0]) > DBM_PBLKSIZ / sizeof(unsigned short))
		return FALSE;

	if G_UNLIKELY(n & 0x1)
		return FALSE;

	if (n > 0) {
		unsigned ino_end = (n + 1) * sizeof(unsigned short);
		off = DBM_PBLKSIZ;
		for (ino++; n > 0; ino += 2) {
			unsigned short koff = offset(ino[0]);
			unsigned short voff = offset(ino[1]);
			if G_UNLIKELY(koff > off || voff > off || voff > koff)
				return FALSE;
			if G_UNLIKELY(koff < ino_end || voff < ino_end)
				return FALSE;
			off = voff;
			n -= 2;
		}
	}
	return TRUE;
}
