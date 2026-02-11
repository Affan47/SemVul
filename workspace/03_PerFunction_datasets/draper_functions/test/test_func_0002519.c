globus_l_job_manager_normalize_date(
    struct tm *                         tm)
{
    int                                 test_year;
    int                                 overflow_days = 0;
    static int                          mday_max[] =
    {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    static int                          mday_leap_max[] =
    {
        31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    do
    {
        if (overflow_days > 0)
        {
            tm->tm_mday = overflow_days;
            tm->tm_mon++;
        }


        if (tm->tm_mon == 12)
        {
            tm->tm_year++;
            tm->tm_mon = 0;
        }

        test_year = tm->tm_year + 1900;
        overflow_days = IS_LEAP_YEAR(test_year)
                ? tm->tm_mday - mday_leap_max[tm->tm_mon]
                : tm->tm_mday - mday_max[tm->tm_mon];
    } while (overflow_days > 0);
}
