ipN_print(register const u_char *bp, register u_int length)
{
	struct ip *ip, hdr;

	ip = (struct ip *)bp;
	if (length < 4) {
		(void)printf("truncated-ip %d", length);
		return;
	}
	memcpy (&hdr, (char *)ip, 4);
	switch (IP_V(&hdr)) {
	case 4:
		ip_print (gndo, bp, length);
		return;
#ifdef INET6
	case 6:
		ip6_print (bp, length);
		return;
#endif
	default:
		(void)printf("unknown ip %d", IP_V(&hdr));
		return;
	}
}
