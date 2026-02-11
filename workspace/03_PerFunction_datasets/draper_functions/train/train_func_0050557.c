ajTimeRefToday(void)
{
    time_t tim;

    if(!timeTodaySaved)
    {
	AJNEW0(timeTodaySaved);

        tim = time(0);

        if(!ajTimeSetLocal(timeTodaySaved, tim))
            return NULL;

        timeTodaySaved->format = NULL;
    }

    return timeTodaySaved;
}
