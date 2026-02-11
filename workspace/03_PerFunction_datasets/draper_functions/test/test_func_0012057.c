AuServerName (const char *name)
{
    if (name && name[0])
	return name;

    name = (const char *) getenv ("AUDIOSERVER");
    if (name)
	return name;

    name = (const char *) getenv ("DISPLAY");
    if (name)
	return name;

    return DEFAULT_AUSERVER;
}
