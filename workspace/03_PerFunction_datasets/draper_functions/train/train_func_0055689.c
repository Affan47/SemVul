ICMPv4line(time_t deltasec, time_t deltatic, time_t hz,
				int ncpu, struct osrel *osr, char *tstamp)
{
	double 		ier, oer, idu, odu, ite, ote, isq, osq, ird, ord;
	struct netstat  *cur, *pre;

	if ( !getcset("netstat", (void **)&cur, (void **)&pre) )
		return(0);

	ier = subtract(cur->icmp.IcmpInErrors,
		      pre->icmp.IcmpInErrors);
	idu = subtract(cur->icmp.IcmpInDestUnreachs,
		      pre->icmp.IcmpInDestUnreachs);
	ite = subtract(cur->icmp.IcmpInTimeExcds,
		      pre->icmp.IcmpInTimeExcds);
	isq = subtract(cur->icmp.IcmpInSrcQuenchs,
		      pre->icmp.IcmpInSrcQuenchs);
	ird = subtract(cur->icmp.IcmpInRedirects,
		      pre->icmp.IcmpInRedirects);
	oer = subtract(cur->icmp.IcmpOutErrors,
		      pre->icmp.IcmpOutErrors);
	odu = subtract(cur->icmp.IcmpOutDestUnreachs,
		      pre->icmp.IcmpOutDestUnreachs);
	ote = subtract(cur->icmp.IcmpOutTimeExcds,
		      pre->icmp.IcmpOutTimeExcds);
	osq = subtract(cur->icmp.IcmpOutSrcQuenchs,
		      pre->icmp.IcmpOutSrcQuenchs);
	ord = subtract(cur->icmp.IcmpOutRedirects,
		      pre->icmp.IcmpOutRedirects);

	printf("%6.2lf %5.2lf %5.2lf %5.2lf %5.2lf "
	       "%6.2lf %5.2lf %5.2lf %5.2lf %5.2lf\n",
		ier / deltasec,
		isq / deltasec,
		ird / deltasec,
		idu / deltasec,
		ite / deltasec,
		oer / deltasec,
		osq / deltasec,
		ord / deltasec,
		odu / deltasec,
		ote / deltasec);

	return(1);
}
