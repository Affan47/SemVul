is_wakeup_enabled(const char *devname)
{
	char	buf[128], *s;
	FILE	*f;


	snprintf(buf, sizeof buf, RTC_PATH, devname + strlen("/dev/"));
	f = fopen(buf, "r");
	if (!f) {
		warn(_("open failed: %s"), buf);
		return 0;
	}
	s = fgets(buf, sizeof buf, f);
	fclose(f);
	if (!s)
		return 0;

	s = strchr(buf, '\n');
	if (!s)
		return 0;
	*s = 0;


	return strcmp(buf, "enabled") == 0;
}
