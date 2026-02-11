set_allowed_addrs(unit, addrs)
    int unit;
    struct wordlist *addrs;
{
    if (addresses[unit] != NULL)
	free_wordlist(addresses[unit]);
    addresses[unit] = addrs;


    if (addrs != NULL && addrs->next == NULL) {
	char *p = addrs->word;
	struct ipcp_options *wo = &ipcp_wantoptions[unit];
	u_int32_t a;
	struct hostent *hp;

	if (*p != '!' && *p != '-' && *p != '*' && strchr(p, '/') == NULL) {
	    hp = gethostbyname(p);
	    if (hp != NULL && hp->h_addrtype == AF_INET)
		a = *(u_int32_t *)hp->h_addr;
	    else
		a = inet_addr(p);
	    if (a != (u_int32_t) -1)
		wo->hisaddr = a;
	}
    }
}
