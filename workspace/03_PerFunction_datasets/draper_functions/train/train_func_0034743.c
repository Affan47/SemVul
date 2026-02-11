print_neighbors2(register const u_char *bp, register const u_char *ep,
    register u_int len)
{
	const u_char *laddr;
	register u_char metric, thresh, flags;
	register int ncount;

	printf(" (v %d.%d):",
	       (int)target_level & 0xff,
	       (int)(target_level >> 8) & 0xff);

	while (len > 0 && bp < ep) {
		TCHECK2(bp[0], 8);
		laddr = bp;
		bp += 4;
		metric = *bp++;
		thresh = *bp++;
		flags = *bp++;
		ncount = *bp++;
		len -= 8;
		while (--ncount >= 0 && (len >= 4) && (bp + 4) <= ep) {
			printf(" [%s -> ", ipaddr_string(laddr));
			printf("%s (%d/%d", ipaddr_string(bp),
				     metric, thresh);
			if (flags & DVMRP_NF_TUNNEL)
				printf("/tunnel");
			if (flags & DVMRP_NF_SRCRT)
				printf("/srcrt");
			if (flags & DVMRP_NF_QUERIER)
				printf("/querier");
			if (flags & DVMRP_NF_DISABLED)
				printf("/disabled");
			if (flags & DVMRP_NF_DOWN)
				printf("/down");
			printf(")]");
			bp += 4;
			len -= 4;
		}
		if (ncount != -1) {
			printf(" [|]");
			return (0);
		}
	}
	return (0);
trunc:
	return (-1);
}
