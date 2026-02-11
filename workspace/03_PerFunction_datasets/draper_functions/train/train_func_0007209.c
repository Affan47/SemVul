ssh1_protocol(Ssh ssh, void *vin, int inlen,
			  struct Packet *pktin)
{
    unsigned char *in=(unsigned char*)vin;
    if (ssh->state == SSH_STATE_CLOSED)
	return;

    if (pktin && ssh->packet_dispatch[pktin->type]) {
	ssh->packet_dispatch[pktin->type](ssh, pktin);
	return;
    }

    if (!ssh->protocol_initial_phase_done) {
	if (do_ssh1_login(ssh, in, inlen, pktin))
	    ssh->protocol_initial_phase_done = TRUE;
	else
	    return;
    }

    do_ssh1_connection(ssh, in, inlen, pktin);
}
