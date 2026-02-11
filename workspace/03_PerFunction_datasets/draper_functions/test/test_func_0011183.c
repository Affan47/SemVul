tgammal(long double x)
{
long double p, q, z;
int i;

if( isnan(x) )
	return(NAN);
if(x == INFINITY)
	return(INFINITY);
if(x == -INFINITY)
	return(x - x);
if( x == 0.0L )
	return( 1.0L / x );
q = fabsl(x);

if( q > 13.0L )
	{
	int sign = 1;
	if( q > MAXGAML )
		goto goverf;
	if( x < 0.0L )
		{
		p = floorl(q);
		if( p == q )
			return (x - x) / (x - x);
		i = p;
		if( (i & 1) == 0 )
			sign = -1;
		z = q - p;
		if( z > 0.5L )
			{
			p += 1.0L;
			z = q - p;
			}
		z = q * sinl( PIL * z );
		z = fabsl(z) * stirf(q);
		if( z <= PIL/LDBL_MAX )
			{
goverf:
			return( sign * INFINITY);
			}
		z = PIL/z;
		}
	else
		{
		z = stirf(x);
		}
	return( sign * z );
	}

z = 1.0L;
while( x >= 3.0L )
	{
	x -= 1.0L;
	z *= x;
	}

while( x < -0.03125L )
	{
	z /= x;
	x += 1.0L;
	}

if( x <= 0.03125L )
	goto small;

while( x < 2.0L )
	{
	z /= x;
	x += 1.0L;
	}

if( x == 2.0L )
	return(z);

x -= 2.0L;
p = __polevll( x, P, 7 );
q = __polevll( x, Q, 8 );
z = z * p / q;
return z;

small:
if( x == 0.0L )
	return (x - x) / (x - x);
else
	{
	if( x < 0.0L )
		{
		x = -x;
		q = z / (x * __polevll( x, SN, 8 ));
		}
	else
		q = z / (x * __polevll( x, S, 8 ));
	}
return q;
}
