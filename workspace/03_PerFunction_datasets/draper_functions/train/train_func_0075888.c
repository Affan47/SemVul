cmpsockaddr(s1, s2)
CONST char *s1, *s2;
{
	struct in_addr *addr1, *addr2;
	int i, j, n, n1, n2;

	if (!strcmp(s1, s2)) return(0);
	if ((n1 = getaddr(s1, &addr1)) < 0) return(-1);
	if ((n2 = getaddr(s2, &addr2)) < 0) return(-1);

	n = -1;
	for (i = 0; i < n1; i++) {
		for (j = 0; j < n2; j++) {
			n = memcmp((char *)&(addr1[i]), (char *)&(addr2[j]),
				sizeof(struct in_addr));
			if (!n) break;
		}
		if (!n) break;
	}
	Xfree(addr1);
	Xfree(addr2);

	return(n);
}
