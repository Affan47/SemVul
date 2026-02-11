erfce(x)
double x;
{
double p,q;

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
return (p/q);
}
