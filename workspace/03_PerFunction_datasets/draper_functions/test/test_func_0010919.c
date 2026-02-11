parseSendmailToLine(char *str, int lenstr)
{
	char *p = str;
	char domain[128];
	char user[128];
	char email[300];
	int i = 0;
	char *tmp = NULL;
	int domainflg = 0;
	char tmpbytes[128];
	int vdomainflg = 0;

	if ((strstr(str, " to=<>")) != NULL) {
		(general.to_cnt)++;
		return;
	}

	if ((p = strstr(p, " to=")) == NULL)
		return;
	if ((p - str) > lenstr)
		return;


	if (strstr(p, " orig_to=") != NULL) {
		p = strstr(p, " orig_to=");
		p += 9;
	} else
		p += 4;

	if (*p == '<')
		p++;

	lowercase(p, strlen(p));
	if ((p - str) > lenstr)
		return;

	for (i = 0; (*p != ',') && (*p != '>') && (*p != '\0') && (*p != '\r') && (*p != '\n') && (i < 127) && ((p - str) < lenstr); i++, p++) {
		if (*p == '@') {
				domainflg = 1;
				break;
		}
		user[i] = *p;
	}
	user[i] = 0x0;

	if (strlen(user) == 0)
		return;

	if (domainflg) {
		p++;
		for (i = 0; (*p != ',') && (*p != '>') && (*p != '\0') && (*p != '\r') && (*p != '\n') && (i < 127) && ((p - str) < lenstr); i++, p++)
			domain[i] = *p;
		domain[i] = 0x0;
		if (strlen(domain) == 0)
			return;
	} else
			strncpy(domain, hostname, 128);

	sprintf(email, "%.128s@%.128s", user, domain);
	checkUser(domain, email, TO_MAIL, 0);
	(general.to_cnt)++;
}
