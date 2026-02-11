getname6(const u_char *ap)
{
	register struct hostent *hp;
	struct in6_addr addr;
	static struct h6namemem *p;
	register const char *cp;
	char ntop_buf[INET6_ADDRSTRLEN];

	memcpy(&addr, ap, sizeof(addr));
	p = &h6nametable[*(u_int16_t *)&addr.s6_addr[14] & (HASHNAMESIZE-1)];
	for (; p->nxt; p = p->nxt) {
		if (memcmp(&p->addr, &addr, sizeof(addr)) == 0)
			return (p->name);
	}
	p->addr = addr;
	p->nxt = newh6namemem();


	if (!nflag) {
		hp = gethostbyaddr((char *)&addr, sizeof(addr), AF_INET6);
		if (hp) {
			char *dotp;

			p->name = strdup(hp->h_name);
			if (Nflag) {

				dotp = strchr(p->name, '.');
				if (dotp)
					*dotp = '\0';
			}
			return (p->name);
		}
	}
	cp = inet_ntop(AF_INET6, &addr, ntop_buf, sizeof(ntop_buf));
	p->name = strdup(cp);
	return (p->name);
}
