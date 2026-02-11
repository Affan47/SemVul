fftm2s(int year,
           int month,
           int day,
           int hour,
           int minute,
           double second,
           int decimals,
           char *datestr,

           int   *status)


{
    int width;
    char errmsg[81];

    if (*status > 0)
        return(*status);

    *datestr='\0';

    if (year != 0 || month != 0 || day !=0)
    {
        if (ffverifydate(year, month, day, status) > 0)
	{
            ffpmsg("invalid date (fftm2s)");
            return(*status);
        }
    }

    if (hour < 0 || hour > 23)
    {
       sprintf(errmsg,
       "input hour value is out of range 0 - 23: %d (fftm2s)", hour);
       ffpmsg(errmsg);
       return(*status = BAD_DATE);
    }
    else if (minute < 0 || minute > 59)
    {
       sprintf(errmsg,
       "input minute value is out of range 0 - 59: %d (fftm2s)", minute);
       ffpmsg(errmsg);
       return(*status = BAD_DATE);
    }
    else if (second < 0. || second >= 61)
    {
       sprintf(errmsg,
       "input second value is out of range 0 - 60.999: %f (fftm2s)", second);
       ffpmsg(errmsg);
       return(*status = BAD_DATE);
    }
    else if (decimals > 25)
    {
       sprintf(errmsg,
       "input decimals value is out of range 0 - 25: %d (fftm2s)", decimals);
       ffpmsg(errmsg);
       return(*status = BAD_DATE);
    }

    if (decimals == 0)
       width = 2;
    else
       width = decimals + 3;

    if (decimals < 0)
    {

        sprintf(datestr, "%.4d-%.2d-%.2d", year, month, day);
    }
    else if (year == 0 && month == 0 && day == 0)
    {

        sprintf(datestr, "%.2d:%.2d:%0*.*f",
            hour, minute, width, decimals, second);
    }
    else
    {

        sprintf(datestr, "%.4d-%.2d-%.2dT%.2d:%.2d:%0*.*f",
            year, month, day, hour, minute, width, decimals, second);
    }
    return(*status);
}
