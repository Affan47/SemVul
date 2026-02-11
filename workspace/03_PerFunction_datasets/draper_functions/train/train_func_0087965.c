julian( int year, int month, int day )
{
	long  total, dayYear ;

	dayYear    =  day_year( year, month, day) ;

	if (dayYear < 1)
		return( -1) ;

	total =  ytoj(year) ;
	total+=  dayYear ;
	total+=  JULIAN_ADJUSTMENT ;

	return total;
}
