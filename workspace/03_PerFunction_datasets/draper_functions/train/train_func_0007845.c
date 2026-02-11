erfc(a)
double a;
{
double p,q,x,y,z;


if( a < 0.0 )
	x = -a;
else
	x = a;

if( x < 1.0 )
	return( 1.0 - erf(a) );

z = -a * a;

if( z < -MAXLOG )
	{
under:
	mtherr( "erfc", UNDERFLOW );
	if( a < 0 )
		return( 2.0 );
	else
		return( 0.0 );
	}

#ifdef USE_EXPXSQ

z = expx2(a, -1);
#else
z = exp(z);
#endif
if( x < 8.0 )
	{
	p = polevl( x, P, 8 );
	q = p1evl( x, Q, 8 );
	}
else
	{
	p = polevl( x, R, 5 );
	q = p1evl( x, S, 6 );
	}
y = (z * p)/q;

if( a < 0 )
	y = 2.0 - y;

if( y == 0.0 )
	goto under;

return(y);
}
