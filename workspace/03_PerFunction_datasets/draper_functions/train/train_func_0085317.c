unixpw_list_match(char *user) {
	if (! unixpw_list || unixpw_list[0] == '\0') {
		return 1;
	} else {
		char *p, *q, *str = strdup(unixpw_list);
		int ok = 0;
		int notmode = 0;

		if (str[0] == '!') {
			notmode = 1;
			ok = 1;
			p = strtok(str+1, ",");
		} else {
			p = strtok(str, ",");
		}
		while (p) {
			if ( (q = strchr(p, ':')) != NULL ) {
				*q = '\0';
			}
			if (!strcmp(user, p)) {
				if (notmode) {
					ok = 0;
				} else {
					ok = 1;
				}
				break;
			}
			if (!notmode && !strcmp("*", p)) {
				ok = 1;
				break;
			}
			p = strtok(NULL, ",");
		}
		free(str);
		if (! ok) {
			rfbLog("unixpw_list_match: fail for '%s'\n", user);
			return 0;
		} else {
			rfbLog("unixpw_list_match: OK for '%s'\n", user);
			return 1;
		}
	}
}
