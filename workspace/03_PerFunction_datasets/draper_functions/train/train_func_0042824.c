GetStaticTimeZoneCode(signed short HourOffset,
			       signed short MinOffset)
{
	for( StaticTimeZone *z = Zones; z->Name; z++ ) {
		if( HourOffset == z->HourOffset && MinOffset == z->MinOffset )
			return z->Code;
	}
	return STATIC_TIME_ZONE_CODE_ERR;
}
