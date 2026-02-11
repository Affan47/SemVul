working_days(time_t start, time_t finish)
{


    trace(("working_days(start = %ld, finish = %ld)\n{\n",
	   (long)start, (long)finish));
    trace(("start = %s", ctime(&start)));
    trace(("finish = %s", ctime(&finish)));
    if (start > finish)
    {
	time_t tmp = start;
	finish = start;
	start = tmp;
    }


    int wday = localtime(&start)->tm_wday;
    wday = (wday + 6) % 7;

    long working_days_whole = 0;
    double working_days_frac = 0;


    if ((long)start + SECONDS_PER_WORKING_DAY <= (long)finish)
    {
	working_days_whole++;
	start += SECONDS_PER_DAY;
	wday = (wday + 1) % 7;
    }


    while ((long)start + SECONDS_PER_WORKING_DAY <= (long)finish)
    {
	if (wday < WORKING_DAYS_PER_WEEK)
    	    working_days_whole++;
	start += SECONDS_PER_DAY;
	wday = (wday + 1) % 7;
    }


    assert((long)finish - (long)start < SECONDS_PER_WORKING_DAY);
    if (start < finish)
    {
	working_days_frac = (finish - start) / (double)SECONDS_PER_WORKING_DAY;
    }


    working_days_frac += working_days_whole;
    trace(("return %.10g;\n", working_days_frac));
    trace(("}\n"));
    return working_days_frac;
}
