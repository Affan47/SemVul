setRetryTime(const char* v)
{
    char* cp;
    u_int t = (u_int) strtoul(v, &cp, 10);
    if (cp) {
	while (isspace(*cp))
	    ;
	if (strncasecmp(cp, "min", 3) == 0)
	    t *= 60;
	else if (strncasecmp(cp, "hour", 4) == 0)
	    t *= 60*60;
	else if (strncasecmp(cp, "day", 3) == 0)
	    t *= 24*60*60;
    }
    retryTime = t;
}
