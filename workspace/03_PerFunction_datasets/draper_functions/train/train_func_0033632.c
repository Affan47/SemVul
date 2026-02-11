stdtr( k, t )
int k;
double t;
{
double x, rk, z, f, tz, p, xsqk;
int j;

if( k <= 0 )
	{
	mtherr( "stdtr", DOMAIN );
	return(0.0);
	}

if( t == 0 )
	return( 0.5 );

if( t < -2.0 )
	{
	rk = k;
	z = rk / (rk + t * t);
	p = 0.5 * incbet( 0.5*rk, 0.5, z );
	return( p );
	}


if( t < 0 )
	x = -t;
else
	x = t;

rk = k;
z = 1.0 + ( x * x )/rk;


if( (k & 1) != 0)
	{


	xsqk = x/sqrt(rk);
	p = atan( xsqk );
	if( k > 1 )
		{
		f = 1.0;
		tz = 1.0;
		j = 3;
		while(  (j<=(k-2)) && ( (tz/f) > MACHEP )  )
			{
			tz *= (j-1)/( z * j );
			f += tz;
			j += 2;
			}
		p += f * xsqk/z;
		}
	p *= 2.0/PI;
	}


else
	{


	f = 1.0;
	tz = 1.0;
	j = 2;

	while(  ( j <= (k-2) ) && ( (tz/f) > MACHEP )  )
		{
		tz *= (j - 1)/( z * j );
		f += tz;
		j += 2;
		}
	p = f * x/sqrt(z*rk);
	}


if( t < 0 )
	p = -p;

	p = 0.5 + 0.5 * p;
return(p);
}
