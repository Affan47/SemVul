str2sa_range(char *str, int *low, int *high)
{
	static struct sockaddr_in sa;
	struct sockaddr_in *ret = NULL;
	char *c;
	int portl, porth;

	memset(&sa, 0, sizeof(sa));
	str = strdup(str);
	if (str == NULL)
		goto out;

	if ((c = strrchr(str,':')) != NULL) {
		char *sep;
		*c++ = '\0';
		sep = strchr(c, '-');
		if (sep)
			*sep++ = '\0';
		else
			sep = c;
		portl = atol(c);
		porth = atol(sep);
	}
	else {
		portl = 0;
		porth = 0;
	}

	if (*str == '*' || *str == '\0') {
		sa.sin_addr.s_addr = INADDR_ANY;
	}
	else if (!inet_pton(AF_INET, str, &sa.sin_addr)) {
		struct hostent *he = gethostbyname(str);
		if (!he)
			goto out;
		sa.sin_addr = *(struct in_addr *) *(he->h_addr_list);
	}
	sa.sin_port   = htons(portl);
	sa.sin_family = AF_INET;
	ret = &sa;

	*low = portl;
	*high = porth;

 out:
	free(str);
	return ret;
}
