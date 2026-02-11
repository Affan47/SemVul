print_probe(register const u_char *bp, register const u_char *ep,
    register u_int len)
{
	register u_int32_t genid;

	TCHECK2(bp[0], 4);
	if ((len < 4) || ((bp + 4) > ep)) {

		printf(" [|}");
		return (0);
	}
	genid = (bp[0] << 24) | (bp[1] << 16) | (bp[2] << 8) | bp[3];
	bp += 4;
	len -= 4;
	if (vflag > 1)
		printf("\n\t");
	else
		printf(" ");
	printf("genid %u", genid);
	if (vflag < 2)
		return (0);

	while ((len > 0) && (bp < ep)) {
		TCHECK2(bp[0], 4);
		printf("\n\tneighbor %s", ipaddr_string(bp));
		bp += 4; len -= 4;
	}
	return (0);
trunc:
	return (-1);
}
