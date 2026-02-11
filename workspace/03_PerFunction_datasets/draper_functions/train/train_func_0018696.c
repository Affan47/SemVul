get_call(int uid)
{
	FILE *fp;
	char buf[256];
	static char call[10];
	int i = 0;

	errno = 0;
	if ((fp = fopen(PROC_AX25_CALLS_FILE, "r")) == NULL)
		return NULL;
	while (fgets(buf, 256, fp) != NULL) {
		if (!i++) continue;
		if (safe_atoi(strtok(buf, " \t\r\n")) == uid) {
			fclose(fp);
			safe_strncpy(call, strtok(NULL, " \t\r\n"), 9);
			return call;
		}
	}
	fclose(fp);
	return NULL;
}
