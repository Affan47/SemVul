ssh1_msg_channel_open_failure(Ssh ssh, struct Packet *pktin)
{
    unsigned int remoteid = ssh_pkt_getuint32(pktin);
    struct ssh_channel *c;

    c = find234(ssh->channels, &remoteid, ssh_channelfind);
    if (c && c->type == CHAN_SOCKDATA_DORMANT) {
	logevent("Forwarded connection refused by server");
	pfd_close(c->u.pfd.s);
	del234(ssh->channels, c);
	sfree(c);
    }
}
