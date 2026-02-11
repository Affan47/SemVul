ip_addr_check(addr, addrs)
    u_int32_t addr;
    struct wordlist *addrs;
{
    u_int32_t a, mask, ah;
    int accept;
    char *ptr_word, *ptr_mask;
    struct hostent *hp;
    struct netent *np;


    if (bad_ip_adrs(addr))
	return 0;

    if (addrs == NULL)
	return 0;

    for (; addrs != NULL; addrs = addrs->next) {

	ptr_word = addrs->word;
	if (strcmp(ptr_word, "-") == 0)
	    break;
	if (strcmp(ptr_word, "*") == 0)
	    return 1;

	accept = 1;
	if (*ptr_word == '!') {
	    accept = 0;
	    ++ptr_word;
	}

	mask = ~ (u_int32_t) 0;
	ptr_mask = strchr (ptr_word, '/');
	if (ptr_mask != NULL) {
	    int bit_count;

	    bit_count = (int) strtol (ptr_mask+1, (char **) 0, 10);
	    if (bit_count <= 0 || bit_count > 32) {
		syslog (LOG_WARNING,
			"invalid address length %s in auth. address list",
			ptr_mask);
		continue;
	    }
	    *ptr_mask = '\0';
	    mask <<= 32 - bit_count;
	}

	hp = gethostbyname(ptr_word);
	if (hp != NULL && hp->h_addrtype == AF_INET) {
	    a = *(u_int32_t *)hp->h_addr;
	} else {
	    np = getnetbyname (ptr_word);
	    if (np != NULL && np->n_addrtype == AF_INET) {
		a = htonl (*(u_int32_t *)np->n_net);
		if (ptr_mask == NULL) {

		    ah = ntohl(a);
		    if (IN_CLASSA(ah))
			mask = IN_CLASSA_NET;
		    else if (IN_CLASSB(ah))
			mask = IN_CLASSB_NET;
		    else if (IN_CLASSC(ah))
			mask = IN_CLASSC_NET;
		}
	    } else {
		a = inet_addr (ptr_word);
	    }
	}

	if (ptr_mask != NULL)
	    *ptr_mask = '/';

	if (a == (u_int32_t)-1L)
	    syslog (LOG_WARNING,
		    "unknown host %s in auth. address list",
		    addrs->word);
	else


	    if (((addr ^ a) & htonl(mask)) == 0)
		return accept;
    }
    return 0;
}
