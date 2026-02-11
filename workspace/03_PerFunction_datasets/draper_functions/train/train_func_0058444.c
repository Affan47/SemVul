lane_hdr_print(register const u_char *bp, int length)
{
	register const struct lecdatahdr_8023 *ep;

	ep = (const struct lecdatahdr_8023 *)bp;
	if (qflag)
		(void)printf("lecid:%x %s %s %d: ",
			     EXTRACT_16BITS(&ep->le_header),
			     etheraddr_string(ep->h_source),
			     etheraddr_string(ep->h_dest),
			     length);
	else
		(void)printf("lecid:%x %s %s %s %d: ",
			     EXTRACT_16BITS(&ep->le_header),
			     etheraddr_string(ep->h_source),
			     etheraddr_string(ep->h_dest),
			     etherproto_string(ep->h_type),
			     length);
}
