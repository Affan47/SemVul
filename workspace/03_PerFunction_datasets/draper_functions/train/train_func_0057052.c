set_dif( set b, set c )
#else
set_dif( b, c )
set b;
set c;
#endif
{


	set t;
	unsigned int n;
	register unsigned *r, *p, *q, *endp;

	CHK(b); CHK(c);
	t = empty;
	n = (b.n <= c.n) ? b.n : c.n ;
	if ( b.n == 0 ) return t;

	set_ext(&t, b.n);
	r = t.setword;


	q = c.setword;
	p = b.setword;
	endp = &(b.setword[n]);
	while ( p < endp ) *r++ = *p++ & (~ *q++);


	if ( b.n > n )
	{
		p = &(b.setword[n]);
		endp = &(b.setword[b.n]);
		while ( p < endp ) *r++ = *p++;
	}

	return(t);
}
