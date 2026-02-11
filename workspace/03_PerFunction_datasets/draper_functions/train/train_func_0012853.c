print_graft_ack(register const u_char *bp)
{
	TCHECK2(bp[0], 8);
	printf(" src %s grp %s", ipaddr_string(bp), ipaddr_string(bp + 4));
	return (0);
trunc:
	return (-1);
}
