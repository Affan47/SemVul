httpd_get_date( const char *str, time_t *date )
{
	char wday[8],month[8];
	int mday, year, hour, minute, second;
	int i;
	struct tm t;

	if( sscanf( str, "%3s, %02d %3s %04d %02d:%02d:%02d GMT", wday, &mday, month, &year, &hour, &minute, &second )!=7 &&
	    sscanf( str, "%6s, %02d-%3s-%02d %02d:%02d:%02d GMT", wday, &mday, month, &year, &hour, &minute, &second )!=7 &&
	    sscanf( str, "%3s %3s %2d %02d:%02d:%02d %04d",       wday, month, &mday, &hour, &minute, &second, &year )!=7 )
		return 0;

	for( i=0; i<12; i++ )
	{
		if( strncasecmp( monthmsg[i], month, 3 )==0 )
			break;
	}
	if( i==12 )
		return 0;
	t.tm_mon = i;

	for( i=0; i<7; i++ )
	{
		if( strncasecmp( weekdaymsg[i], wday, 3 )==0 )
			break;
	}
	if( i==7 )
		return 0;
	t.tm_wday  = i;

	t.tm_sec  = second;
	t.tm_min  = minute;
	t.tm_hour = hour;
	t.tm_mday = mday;
	t.tm_year = (year>=1900)? year-1900 : year;
	t.tm_isdst= 0;

	*date = mktime( &t ) - tz*60;

	return 1;
}
