iso_mktime(const char *timestamp)
{
	bool utc, zone;
	struct tm t;
	int zoneminutes;
	if( !iso_to_tm(timestamp, &t, utc, &zone, &zoneminutes) )
		return (time_t)-1;

	TzWrapper tzw;
	if( utc ) {
		tzw.SetUTC();
	}
	else if( zone ) {
		tzw.SetOffset(zoneminutes);
	}
	return tzw.mktime(&t);
}
