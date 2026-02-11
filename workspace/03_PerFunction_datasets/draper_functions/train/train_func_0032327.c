get_time(struct tm *rectime, int d_off)
{
	static int utc = 0;
	char *e;

	if (!utc) {

		if ((e = getenv(ENV_TIME_DEFTM)) != NULL) {
			utc = !strcmp(e, K_UTC);
		}
		utc++;
	}

	if (utc == 2)
		return get_gmtime(rectime, d_off);
	else
		return get_localtime(rectime, d_off);
}
