get_hostname(char* addr)
{
	static char answer[1024];
	static char lastreq[1024] = {'\0'};
	struct hostent *he;
	struct in_addr naddr;
	static char *last_answerp = NULL;

	printf(" get hostname..."); fflush(stdout);
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
		"               "
		"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");

	if (!strcmp(addr, lastreq))
		return last_answerp;

	strlcpy(lastreq, addr, 1024);
	inet_aton(addr, &naddr);
	he = gethostbyaddr((char*)&naddr, 4, AF_INET);

	if (he == NULL) {
		last_answerp = NULL;
		return NULL;
	}

	strlcpy(answer, he->h_name, 1024);
	last_answerp = answer;

	return answer;
}
