mapBool(char *p, boolean dflt)
{
    if (!p || (*p == '\0'))
	return dflt;
    if (!strcasecmp(p, "false"))
	return FALSE;
    if (!strcasecmp(p, "no"))
	return FALSE;
    if (!strcasecmp(p, "true"))
	return TRUE;
    if (!strcasecmp(p, "yes"))
	return TRUE;
    if (isdigit(*p))
	return atoi(p);
    else
	return dflt;
}
