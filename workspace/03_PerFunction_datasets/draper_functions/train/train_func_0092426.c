ellpk(x)
double x;
{

if( (x < 0.0) || (x > 1.0) )
	{
	mtherr( "ellpk", DOMAIN );
	return( 0.0 );
	}

if( x > MACHEP )
	{
	return( polevl(x,P,10) - log(x) * polevl(x,Q,10) );
	}
else
	{
	if( x == 0.0 )
		{
		mtherr( "ellpk", SING );
		return( MAXNUM );
		}
	else
		{
		return( C1 - 0.5 * log(x) );
		}
	}
}
