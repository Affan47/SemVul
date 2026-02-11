iso8601wknum(const struct tm *timeptr)
#endif
{


	int weeknum, jan1day;


	weeknum = weeknumber(timeptr, 1);


	jan1day = timeptr->tm_wday - (timeptr->tm_yday % 7);
	if (jan1day < 0)
		jan1day += 7;


	switch (jan1day) {
	case 1:
		break;
	case 2:
	case 3:
	case 4:
		weeknum++;
		break;
	case 5:
	case 6:
	case 0:
		if (weeknum == 0) {
#ifdef USE_BROKEN_XPG4

			weeknum = 53;
#else

			struct tm dec31ly;
			dec31ly = *timeptr;
			dec31ly.tm_year--;
			dec31ly.tm_mon = 11;
			dec31ly.tm_mday = 31;
			dec31ly.tm_wday = (jan1day == 0) ? 6 : jan1day - 1;
			dec31ly.tm_yday = 364 + isleap(dec31ly.tm_year + 1900L);
			weeknum = iso8601wknum(& dec31ly);
#endif
		}
		break;
	}

	if (timeptr->tm_mon == 11) {


		int wday, mday;

		wday = timeptr->tm_wday;
		mday = timeptr->tm_mday;
		if (   (wday == 1 && (mday >= 29 && mday <= 31))
		    || (wday == 2 && (mday == 30 || mday == 31))
		    || (wday == 3 &&  mday == 31))
			weeknum = 1;
	}

	return weeknum;
}
