ziplocal_TmzDateToDosDate(ptm,dosDate)
    const tm_zip* ptm;
    uLong dosDate;
{
	#ifndef _WINDOWS
    (void) dosDate;
	#endif

    uLong year = (uLong)ptm->tm_year;
    if (year>1980)
        year-=1980;
    else if (year>80)
        year-=80;
    return
      (uLong) (((ptm->tm_mday) + (32 * (ptm->tm_mon+1)) + (512 * year)) << 16) |
        ((ptm->tm_sec/2) + (32* ptm->tm_min) + (2048 * (uLong)ptm->tm_hour));
}
