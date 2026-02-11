ssh1_msg_port_open(Ssh ssh, struct Packet *pktin)
{


    struct ssh_channel *c;
    struct ssh_rportfwd pf, *pfp;
    int remoteid;
    int hostsize, port;
    char *host;
    const char *e;
    c = snew(struct ssh_channel);
    c->ssh = ssh;

    remoteid = ssh_pkt_getuint32(pktin);
    ssh_pkt_getstring(pktin, &host, &hostsize);
    port = ssh_pkt_getuint32(pktin);

    if (hostsize >= lenof(pf.dhost))
	hostsize = lenof(pf.dhost)-1;
    memcpy(pf.dhost, host, hostsize);
    pf.dhost[hostsize] = '\0';
    pf.dport = port;
    pfp = find234(ssh->rportfwds, &pf, NULL);

    if (pfp == NULL) {
	logeventf(ssh, "Rejected remote port open request for %s:%d",
		  pf.dhost, port);
	send_packet(ssh, SSH1_MSG_CHANNEL_OPEN_FAILURE,
		    PKT_INT, remoteid, PKT_END);
    } else {
	logeventf(ssh, "Received remote port open request for %s:%d",
		  pf.dhost, port);
	e = pfd_newconnect(&c->u.pfd.s, pf.dhost, port,
			   c, &ssh->cfg, pfp->pfrec->addressfamily);
	if (e != NULL) {
	    logeventf(ssh, "Port open failed: %s", e);
	    sfree(c);
	    send_packet(ssh, SSH1_MSG_CHANNEL_OPEN_FAILURE,
			PKT_INT, remoteid, PKT_END);
	} else {
	    c->remoteid = remoteid;
	    c->halfopen = FALSE;
	    c->localid = alloc_channel_id(ssh);
	    c->closes = 0;
	    c->pending_close = FALSE;
	    c->throttling_conn = 0;
	    c->type = CHAN_SOCKDATA;
	    add234(ssh->channels, c);
	    send_packet(ssh, SSH1_MSG_CHANNEL_OPEN_CONFIRMATION,
			PKT_INT, c->remoteid, PKT_INT,
			c->localid, PKT_END);
	    logevent("Forwarded port opened successfully");
	}
    }
}
