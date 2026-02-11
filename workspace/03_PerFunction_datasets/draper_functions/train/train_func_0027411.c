shut_host(const netid_t hostid)
{
	struct	remote	*rp;

	if  ((rp = inl_find_connected(hostid)))  {
		unsigned	snore;
		struct	netmsg	rq;
		rq.code = htons(SN_SHUTHOST);
		rq.seq = htons(rp->ht_seqto);
		rq.hostid = myhostid;
		rq.arg = 0;
		chk_write(rp, (char *) &rq, sizeof(rq));
		for  (snore = closedelay;  snore != 0;  snore = sleep(snore))
			;
	}
}
