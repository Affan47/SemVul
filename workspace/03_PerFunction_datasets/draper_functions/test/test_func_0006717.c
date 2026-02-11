answer_askall(const netid_t whofrom, struct ua_pal *inmsg, const int inlng)
{
	int	cnt;
	struct	hhash	*hp;
	struct	ua_pal	reply;

	BLOCK_ZERO(&reply, sizeof(reply));
	reply.uap_op = SV_SV_LOGGEDU;

	if  (inlng != sizeof(struct ua_pal)  ||
	     (whofrom != myhostid && whofrom != localhostid  &&
	      !((hp = find_remote(whofrom))  &&  hp->rem.ht_flags & HT_TRUSTED)))
		return;

	for  (cnt = 0;  cnt < NETHASHMOD;  cnt++)  {
		for  (hp = nhashtab[cnt];  hp;  hp = hp->hn_next)  {
			if  (!(hp->rem.ht_flags & HT_ROAMUSER))
				continue;
			if  (hp->flags != UAL_OK)
				continue;
			reply.uap_netid = hp->rem.hostid;
			strncpy(reply.uap_name, hp->actname, UIDSIZE);
			strncpy(reply.uap_wname, hp->dosname, UIDSIZE);
			udp_send_to((char *) &reply, sizeof(reply), whofrom);
		}
	}
	if  (tracing & TRACE_SYSOP)
		client_trace_op(whofrom, "askall done");
}
