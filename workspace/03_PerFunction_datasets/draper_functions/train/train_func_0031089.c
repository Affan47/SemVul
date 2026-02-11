zgetdate()
{
double J;


getnum( "Calendar date: Year", &cyear, lngfmt );

if( (cyear > 53994L) || (cyear < -4713L) )
	{
	printf( "Year out of range.\n" );
	goto err;
	}
if( cyear == 0 )
	{
	printf( "There is no year 0.\n" );
err:	J = 0.0;
	goto pdate;
	}

getnum( "Month (1-12)", &month, intfmt);
getnum( "Day.fraction", &day, dblfmt );


J = caltoj(cyear,month,day);


pdate:


return(J);
}
