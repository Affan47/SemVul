linux_version_code()
{
#ifdef __linux__
	struct utsname	ut;
	static		version_code = -1;
	int		major, minor, rev;
	char		*endptr;
	const char 	*cp;

	if (version_code > 0)
		return version_code;

	if (uname(&ut))
		return 0;
	cp = ut.release;

	major = strtol(cp, &endptr, 10);
	if (cp == endptr || *endptr != '.')
		return 0;
	cp = endptr + 1;
	minor = strtol(cp, &endptr, 10);
	if (cp == endptr || *endptr != '.')
		return 0;
	cp = endptr + 1;
	rev = strtol(cp, &endptr, 10);
	if (cp == endptr)
		return 0;
	version_code = (((major * 256) + minor) * 256) + rev;
	return version_code;
#else
	return 0;
#endif
}
