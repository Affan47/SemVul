tcpline(time_t deltasec, time_t deltatic, time_t hz,
				int ncpu, struct osrel *osr, char *tstamp)
{
	double		is, os, ao, po;
	unsigned long	sn=0, sm=0;
	struct netstat 	*cur,  *pre;
	struct sockstat	*scur, *spre;

	if ( !getcset("netstat", (void **)&cur, (void **)&pre) )
		return(0);

	if ( getcset("sockstat", (void **)&scur, (void **)&spre) )
	{
		sn = scur->tcpnow;
		sm = scur->tcpmax;
	}

	is = subtract(cur->tcp.TcpInSegs,       pre->tcp.TcpInSegs);
	os = subtract(cur->tcp.TcpOutSegs,      pre->tcp.TcpOutSegs);
	ao = subtract(cur->tcp.TcpActiveOpens,  pre->tcp.TcpActiveOpens);
	po = subtract(cur->tcp.TcpPassiveOpens, pre->tcp.TcpPassiveOpens);

	printf("%8.1lf %8.1lf %9.1lf %9.1lf  %7lld  %7ld %7ld\n",
		is / deltasec,
		os / deltasec,
		ao / deltasec,
		po / deltasec,
		cur->tcp.TcpCurrEstab,
		sn, sm);

	return(1);
}
