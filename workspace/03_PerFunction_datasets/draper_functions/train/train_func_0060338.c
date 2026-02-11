set_andin( set *a, set b )
#else
set_andin( a, b )
set *a;
set b;
#endif
{


	unsigned int m;
	register unsigned *p,
					  *q    = b.setword,
					  *endq = &(b.setword[b.n]);

	CHK((*a)); CHK(b);
	if ( b.n == 0 ) return;
	m = (a->n > b.n) ? a->n : b.n;
	set_ext(a, m);
	p = a->setword;
	do {
		*p++ &= *q++;
	} while ( q < endq );
}
