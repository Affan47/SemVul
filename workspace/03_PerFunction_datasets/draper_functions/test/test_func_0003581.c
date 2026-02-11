newhost(void)
{
	int	newsock;
	struct	remote	*rp;
	struct	haship	**hipp, *hip;
	struct	sockaddr_in	sin;
	SOCKLEN_T	sinl;

	sinl = sizeof(sin);
	if  ((newsock = accept(listsock, (struct sockaddr *) &sin, &sinl)) < 0)
		return;

	hipp = get_pp_haship((netid_t) sin.sin_addr.s_addr);

	if  (!(hip = *hipp))  {
		struct	netmsg		rq;
		struct  hostent  *hp;
		rq.code = htons(SN_SHUTHOST);
		rq.hostid = myhostid;
		rq.arg = 0;
		write(newsock, (char *) &rq, sizeof(rq));
		hp = gethostbyaddr((char *) &sin.sin_addr.s_addr, sizeof(netid_t), AF_INET);
		disp_str = hp? hp->h_name: inet_ntoa(sin.sin_addr);
		nfreport(8126);
		close(newsock);
		return;
	}


	rp = reass_hip(hip);
	rp->is_sync = NSYNC_OK;
	rp->ht_flags &= ~HT_ISCLIENT;
	rp->sockfd = (SHORT) newsock;
	rp->lastwrite = time((time_t *) 0);
	rp->ht_seqto = rp->ht_seqfrom = 0;
}
