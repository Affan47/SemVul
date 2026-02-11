gammln (double x)
{
	double p, q, w, z;
	int i;

	sgngam = 1;

	if( x < -34.0 )
		{
		q = -x;
		w = gammln(q);
		p = floor(q);
		if( p == q )
			goto loverf;
		i = (int)p;
		if( (i & 1) == 0 )
			sgngam = -1;
		else
			sgngam = 1;
		z = q - p;
		if( z > 0.5 )
			{
			p += 1.0;
			z = p - q;
			}
		z = q * sin( PI * z );
		if( z == 0.0 )
			goto loverf;

		z = LOGPI - log( z ) - w;
		return( z );
		}

	if( x < 13.0 )
		{
		z = 1.0;
		while( x >= 3.0 )
			{
			x -= 1.0;
			z *= x;
			}
		while( x < 2.0 )
			{
			if( x == 0.0 )
				goto loverf;
			z /= x;
			x += 1.0;
			}
		if( z < 0.0 )
			{
			sgngam = -1;
			z = -z;
			}
		else
			sgngam = 1;
		if( x == 2.0 )
			return( log(z) );
		x -= 2.0;
		p = x * polevl( x, B, 5 ) / p1evl( x, C, 6);
		return( log(z) + p );
		}

	if( x > MAXLGM )
		{
	loverf:
		output("Overflow in loggamma\n");
		error=1; return 0;
		}

	q = ( x - 0.5 ) * log(x) - x + LS2PI;
	if( x > 1.0e8 )
		return( q );

	p = 1.0/(x*x);
	if( x >= 1000.0 )
		q += ((   7.9365079365079365079365e-4 * p
			- 2.7777777777777777777778e-3) *p
			+ 0.0833333333333333333333) / x;
	else
		q += polevl( p, A, 4 ) / x;
	return( q );
}
