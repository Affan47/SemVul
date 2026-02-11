gmformat_time_t (time_t unixtime)
{
    static char buf[sizeof ("yyyy-mm-dd HH:MM:SS -HHMM")];

    struct tm ltm = *(gmtime (&unixtime));

    if (!my_strftime (buf, sizeof (buf), "%Y-%m-%d %H:%M:%S %z", &ltm, 0, 0))
	return NULL;

    return xstrdup (buf);
}
