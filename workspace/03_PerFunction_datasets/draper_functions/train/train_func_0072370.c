BreakItemDelay(char *id)
#else
BreakItemDelay(id)
    char *id;
#endif
{
    char *p;
    int delay;

    CONDDEBUG((1, "BreakItemDelay(%s) [%s:%d]", id, file, line));

    if ((id == (char *)0) || (*id == '\000')) {
	parserBreakDelay = 0;
	return;
    }

    for (p = id; *p != '\000'; p++)
	if (!isdigit((int)(*p)))
	    break;

    if ((*p != '\000') || ((delay = atoi(id)) > 999)) {
	if (isMaster)
	    Error("invalid delay number `%s' [%s:%d]", id, file, line);
	return;
    }
    parserBreakDelay = delay;
}
