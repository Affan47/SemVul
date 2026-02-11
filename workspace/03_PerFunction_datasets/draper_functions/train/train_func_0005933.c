uip_connect(struct uip_stack *ustack, uip_ip4addr_t *ripaddr,
			     u16_t rport)
{
	u8_t c;
	register struct uip_conn *conn, *cconn;


again:
	++ustack->lastport;

	if (ustack->lastport >= 32000)
		ustack->lastport = 4096;


	for (c = 0; c < UIP_CONNS; ++c) {
		conn = &ustack->uip_conns[c];
		if (conn->tcpstateflags != UIP_CLOSED &&
		    conn->lport == htons(ustack->lastport)) {
			goto again;
		}
	}

	conn = 0;
	for (c = 0; c < UIP_CONNS; ++c) {
		cconn = &ustack->uip_conns[c];
		if (cconn->tcpstateflags == UIP_CLOSED) {
			conn = cconn;
			break;
		}
		if (cconn->tcpstateflags == UIP_TIME_WAIT) {
			if (conn == 0 || cconn->timer > conn->timer)
				conn = cconn;
		}
	}

	if (conn == 0)
		return 0;

	conn->tcpstateflags = UIP_SYN_SENT;

	conn->snd_nxt[0] = ustack->iss[0];
	conn->snd_nxt[1] = ustack->iss[1];
	conn->snd_nxt[2] = ustack->iss[2];
	conn->snd_nxt[3] = ustack->iss[3];

	conn->initialmss = conn->mss = UIP_TCP_MSS;

	conn->len = 1;
	conn->nrtx = 0;
	conn->timer = 1;
	conn->rto = UIP_RTO;
	conn->sa = 0;
	conn->sv = 16;
	conn->lport = htons(ustack->lastport);
	conn->rport = rport;
	uip_ip4addr_copy(&conn->ripaddr, ripaddr);

	return conn;
}
