lutil_tm2time( struct lutil_tm *tm, struct lutil_timet *tt )
{
	static int moffset[12] = {
		0, 31, 59, 90, 120,
		151, 181, 212, 243,
		273, 304, 334 };
	int sec;

	tt->tt_usec = tm->tm_usec;


	if ( tm->tm_year == -1900 && tm->tm_mon == 0 && tm->tm_mday == 1 &&
		tm->tm_hour == 0 && tm->tm_min == 0 && tm->tm_sec == 0 ) {
		tt->tt_sec = 0;
		tt->tt_gsec = 0;
		return 0;
	}


	tt->tt_sec = tm->tm_year - 70;
	tt->tt_sec *= 365L;


	tt->tt_sec += ((tm->tm_year -69) >> 2);


	tt->tt_sec += moffset[tm->tm_mon];


	if (((tm->tm_year & 3) == 0) && (tm->tm_mon > 1)) {
		tt->tt_sec ++;
	}


	tt->tt_sec += (tm->tm_mday - 1);


	tt->tt_sec *= 675;


	tt->tt_gsec = tt->tt_sec >> 25;
	tt->tt_sec -= tt->tt_gsec << 25;


	sec = tm->tm_hour;


	sec *= 60L;
	sec += tm->tm_min;


	sec *= 60L;
	sec += tm->tm_sec;


	tt->tt_sec <<= 7;
	tt->tt_sec += sec;


	return 0;
}
