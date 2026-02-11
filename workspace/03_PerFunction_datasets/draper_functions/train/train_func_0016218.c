jtocal( J )
double J;
{
int month, day;
long year, a, c, d, x, y, jd;
int BC;
double dd;

if( J < 1721425.5 )
	BC = 1;
else
	BC = 0;

jd = (long) (J + 0.5);


a = (100*jd + 3204500L)/3652425L;


c = jd + 1486;
if( jd >= 2299160.5 )
	c += a - a/4;
else
	c += 38;


d = (100*c - 12210L)/36525L;

x = (36525L * d)/100L;


y = ((c-x)*100L)/3061L;
day = (int) (c - x - ((306L*y)/10L));
month = (int) (y - 1);
if( y > 13 )
	month -= 12;


year = d - 4715;
if( month > 2 )
	year -= 1;


a = (jd + 1) % 7;


dd = day + J - jd + 0.5;


cyear = year;

if( BC )
	{
	year = -year + 1;
	cyear = -year;
	if( prtflg )
		printf( "%ld B.C. ", year );
	}
else
	{
	if( prtflg )
		printf( "%ld ", year );
	}
day = (int) dd;
if( prtflg )
	printf( "%s %d %s", months[month-1], day, days[(int) a] );


if( ((month == 1) && (day == 1))
	|| ((month == 12) && (day == 31)) )
	yerend = 1;
else
	yerend = 0;


a = (long) dd;
dd = dd - a;
if( prtflg )
	{
	hms( 2.0*PI*dd );
	if( J == TDT )
		printf( "TDT\n" );
	else if( J == UT )
		printf( "UT\n" );
	else
		printf( "\n" );
	}
return(0);
}
