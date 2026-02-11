check_syslog_date(char *buf, int buflen)
{
	unsigned char m[4]= {0};
	int day = 0, i = 0, j;

	for (i = 0; buf[i] != ' ' && buf[i] != '\n' && buf[i] != EOF && i < 4; i++)
		m[i] = buf[i];

	m[3] = '\0';

	while(buf[i] ==' ' && i < buflen)
		i++;

	for (j = i++; buf[j] != ' ' && buf[j] != '\n' && buf[j] != EOF && j < buflen; j++)
		day =  10 * day + (buf[j] - '0');

	if ((strncmp(months[cur_month -1], m, 3) == 0) && (day == cur_day ))
		return 1;

	return -1;
}
