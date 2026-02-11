etherproto_string(u_short port)
{
	register char *cp;
	register struct hnamemem *tp;
	register u_int32_t i = port;
	char buf[sizeof("0000")];

	for (tp = &eprototable[i & (HASHNAMESIZE-1)]; tp->nxt; tp = tp->nxt)
		if (tp->addr == i)
			return (tp->name);

	tp->addr = i;
	tp->nxt = newhnamemem();

	cp = buf;
	NTOHS(port);
	*cp++ = hex[port >> 12 & 0xf];
	*cp++ = hex[port >> 8 & 0xf];
	*cp++ = hex[port >> 4 & 0xf];
	*cp++ = hex[port & 0xf];
	*cp++ = '\0';
	tp->name = strdup(buf);
	return (tp->name);
}
