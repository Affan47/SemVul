GetPort(const char *str, short defaultport)
{
	const char *colon = strchr(str, ':');
	if (colon) {
		return atoi(colon+1);
	}
	else {
		return defaultport;
	}
}
