unalias(const char *name)
{
	struct alias **app;

	app = __lookupalias(name);

	if (*app) {
		INT_OFF;
		*app = freealias(*app);
		INT_ON;
		return 0;
	}

	return 1;
}
