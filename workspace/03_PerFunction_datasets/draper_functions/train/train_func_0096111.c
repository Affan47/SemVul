version_stamp(const char *str, version_t *ver)
{
	static char stamp[256];
	const char *p;

	ver->timestamp = 0;


	p = strchr(str, '(');
	if (p) {
		const char *end;

		p++;
		end = strchr(p, ';');
		if (end == NULL)
			end = strchr(p, ')');
		if (end) {
			size_t size = end - p + 1;


			g_strlcpy(stamp, p, MIN(size, sizeof(stamp)));
			ver->timestamp = date2time(stamp, tm_time());

			if (ver->timestamp == -1) {
				ver->timestamp = 0;
				g_warning("could not parse timestamp \"%s\" in \"%s\"", p, str);
			}
		} else
			g_warning("no timestamp in \"%s\"", str);
	}
}
