tcpv6line(time_t deltasec, time_t deltatic, time_t hz,
				int ncpu, struct osrel *osr, char *tstamp)
{
	unsigned long	sn=0, sm=0;
	struct sockstat	*scur, *spre;

	if ( getcset("sockstat", (void **)&scur, (void **)&spre) )
	{
		sn = scur->tcp6now;
		sm = scur->tcp6max;
	}

	printf("                                       "
	       "       %7ld %7ld\n", sn, sm);

	return(1);
}
