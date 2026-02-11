parseBytesLine(squid_off_t * bptr, const char *units)
{
    char *token;
    double d;
    squid_off_t m;
    squid_off_t u;
    if ((u = parseBytesUnits(units)) == 0)
	self_destruct();
    if ((token = strtok(NULL, w_space)) == NULL)
	self_destruct();
    if (strcmp(token, "none") == 0 || strcmp(token, "-1") == 0) {
	*bptr = (squid_off_t) - 1;
	return;
    }
    d = xatof(token);
    m = u;
    if (0.0 == d)
	(void) 0;
    else if ((token = strtok(NULL, w_space)) == NULL)
	debug(3, 0) ("WARNING: No units on '%s', assuming %f %s\n",
	    config_input_line, d, units);
    else if ((m = parseBytesUnits(token)) == 0)
	self_destruct();
    *bptr = m * d / u;
    if ((double) *bptr * 2 != m * d / u * 2)
	self_destruct();
}
