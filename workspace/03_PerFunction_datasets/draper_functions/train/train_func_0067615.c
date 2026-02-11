print_times(time_t t, char buf[64])
{
    if (t)
	strftime(buf, 64, "%m-%dT%H:%M", gmtime(&t));
    else
	strlcpy(buf, "never", 64);
}
