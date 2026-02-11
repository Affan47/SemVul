readSpecialLogFile(char *fn, int year, int month, int day)
{
	FILE *fp = NULL;
	char buf[1024];
	int i = 0;

	if ((fp = fopen(fn, "r")) == NULL) {
		fprintf(stderr, "open file: %s %s\n", fn, strerror(errno));
		exit(-1);
	}
	while ((fgets(buf, 1024, fp)) != NULL)
		if ((timeconvert(buf, 1024, year, month, day, &i)) > 0) {
			if ((strstr(buf, " from ")) != NULL)
				parseQmailFromBytesLine(buf, strlen(buf));
			else if ((strstr(buf, " to remote")) != NULL)
				parseQmailToRemoteLine(buf, strlen(buf));
			else if ((strstr(buf, " to local")) != NULL)
				parseQmailToLocalLine(buf, strlen(buf));
			}
	fclose(fp);
}
