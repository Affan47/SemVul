monthadd(time_t sdate, time_t arelmonth)
{
    struct tm       *ltime;
    int             amm;
    int             ayear;
    time_t          result;

    trace(("monthadd(sdate = %ld, arelmonth = %ld)\n{\n",
	(long)sdate, (long)arelmonth));
    if (arelmonth == 0)
	result = 0;
    else
    {
	ltime = localtime(&sdate);
	amm = 12 * (ltime->tm_year + 1900) + ltime->tm_mon + arelmonth;
	ayear = amm / 12;
	amm = amm % 12 + 1;
	result =
	    dateconv
	    (
	       	amm,
	       	ltime->tm_mday,
	       	ayear,
	       	ltime->tm_hour,
	       	ltime->tm_min,
	       	ltime->tm_sec,
	       	24,
	       	ourzone,
	       	MAYBE
	    );
	if (result >= 0)
	    result = daylcorr(result, sdate);
    }
    trace(("return %ld;\n", (long)result));
    trace(("}\n"));
    return result;
}
