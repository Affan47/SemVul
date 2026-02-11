log10l(long double x)
{
long double y;
volatile long double z;
int e;

if( isnan(x) )
	return(x);

if( x <= 0.0L )
	{
	if( x == 0.0L )
		return (-1.0L / (x - x));
	else
		return (x - x) / (x - x);
	}
if( x == INFINITY )
	return(INFINITY);


x = frexpl( x, &e );


if( (e > 2) || (e < -2) )
{
if( x < SQRTH )
	{
	e -= 1;
	z = x - 0.5L;
	y = 0.5L * z + 0.5L;
	}
else
	{
	z = x - 0.5L;
	z -= 0.5L;
	y = 0.5L * x  + 0.5L;
	}
x = z / y;
z = x*x;
y = x * ( z * __polevll( z, R, 3 ) / __p1evll( z, S, 3 ) );
goto done;
}


if( x < SQRTH )
	{
	e -= 1;
	x = ldexpl( x, 1 ) - 1.0L;
	}
else
	{
	x = x - 1.0L;
	}
z = x*x;
y = x * ( z * __polevll( x, P, 6 ) / __p1evll( x, Q, 7 ) );
y = y - ldexpl( z, -1 );

done:


z = y * (L10EB);
z += x * (L10EB);
z += e * (L102B);
z += y * (L10EA);
z += x * (L10EA);
z += e * (L102A);

return( z );
}
