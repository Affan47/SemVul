match_hostname(const char **host_ptr, const char *addr, const char *tok)
{
	struct hostent *hp;
	unsigned int i;
	const char *host = *host_ptr;

	if (!host || !*host)
		return 0;


	if (iwildmatch(tok, host))
		return 1;

	if (!allow_forward_dns)
		return 0;


	if (!tok[strspn(tok, ".0123456789")] || tok[strcspn(tok, ":/*?[")])
		return 0;


	if (!(hp = gethostbyname(tok)))
		return 0;

	for (i = 0; hp->h_addr_list[i] != NULL; i++) {
		if (strcmp(addr, inet_ntoa(*(struct in_addr*)(hp->h_addr_list[i]))) == 0) {


			if (host == undetermined_hostname) {
				if (!(*host_ptr = strdup(tok)))
					*host_ptr = undetermined_hostname;
			}
			return 1;
		}
	}

	return 0;
}
