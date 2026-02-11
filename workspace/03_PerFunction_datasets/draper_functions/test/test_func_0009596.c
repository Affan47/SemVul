copytobuf(struct hostent *he, struct hostent *hptr, char *buf, int buflen) {
	char *cp;
	char **ptr;
	int i, n;
	int nptr, len;


	nptr = 2;
	len = (int)((char *)LWRES_ALIGN(buf) - buf);
	for (i = 0; he->h_addr_list[i]; i++, nptr++) {
		len += he->h_length;
	}
	for (i = 0; he->h_aliases[i]; i++, nptr++) {
		len += strlen(he->h_aliases[i]) + 1;
	}
	len += strlen(he->h_name) + 1;
	len += nptr * sizeof(char*);

	if (len > buflen) {
		return (-1);
	}


	hptr->h_addrtype = he->h_addrtype;
	n = hptr->h_length = he->h_length;

	ptr = (char **)LWRES_ALIGN(buf);
	cp = (char *)LWRES_ALIGN(buf) + nptr * sizeof(char *);


	hptr->h_addr_list = ptr;
	for (i = 0; he->h_addr_list[i]; i++, ptr++) {
		memmove(cp, he->h_addr_list[i], n);
		hptr->h_addr_list[i] = cp;
		cp += n;
	}
	hptr->h_addr_list[i] = NULL;
	ptr++;


	n = strlen(he->h_name) + 1;
	strcpy(cp, he->h_name);
	hptr->h_name = cp;
	cp += n;


	hptr->h_aliases = ptr;
	for (i = 0; he->h_aliases[i]; i++) {
		n = strlen(he->h_aliases[i]) + 1;
		strcpy(cp, he->h_aliases[i]);
		hptr->h_aliases[i] = cp;
		cp += n;
	}
	hptr->h_aliases[i] = NULL;

	return (0);
}
