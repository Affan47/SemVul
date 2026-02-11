_set_pdq( set a, register unsigned *q )
#else
_set_pdq( a, q )
set a;
register unsigned *q;
#endif
{
	register unsigned *p = a.setword,
					  *endp = &(a.setword[a.n]);
	register unsigned e=0;

	CHK(a);

	if ( a.n == 0 ) return;
	do {
		register unsigned t = *p;
		register unsigned *b = &(bitmask[0]);
		do {
			if ( t & *b ) *q++ = e;
			++e;
		} while (++b < &(bitmask[WORDSIZE]));
	} while (++p < endp);
	*q = nil;
}
