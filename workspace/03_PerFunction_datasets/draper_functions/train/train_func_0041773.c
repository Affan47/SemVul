driver_loaded(char *driver)
{
	static char *fn = "/proc/capi/driver";
	char buf[4096];
	FILE *fp;

	if (strcmp(driver, "b1pciv4") == 0)
		driver = "b1pci";

	if ((fp = fopen_with_errmsg(fn, "r")) == NULL)
		return 0;
	while (fgets(buf,sizeof(buf),fp)) {
		char *s = buf;
		while (*s && !isspace(*s)) s++;
		*s = 0;
		if (strcmp(buf, driver) == 0) {
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}
