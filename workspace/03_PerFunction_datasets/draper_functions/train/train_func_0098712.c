create_tunnel(struct l2tp_parm *p)
{
	uint32_t local_attr = L2TP_ATTR_IP_SADDR;
	uint32_t peer_attr = L2TP_ATTR_IP_DADDR;

	GENL_REQUEST(req, 1024, genl_family, 0, L2TP_GENL_VERSION,
		     L2TP_CMD_TUNNEL_CREATE, NLM_F_REQUEST | NLM_F_ACK);

	addattr32(&req.n, 1024, L2TP_ATTR_CONN_ID, p->tunnel_id);
	addattr32(&req.n, 1024, L2TP_ATTR_PEER_CONN_ID, p->peer_tunnel_id);
	addattr8(&req.n, 1024, L2TP_ATTR_PROTO_VERSION, 3);
	addattr16(&req.n, 1024, L2TP_ATTR_ENCAP_TYPE, p->encap);

	if (p->local_ip.family == AF_INET6)
		local_attr = L2TP_ATTR_IP6_SADDR;
	addattr_l(&req.n, 1024, local_attr, &p->local_ip.data, p->local_ip.bytelen);

	if (p->peer_ip.family == AF_INET6)
		peer_attr = L2TP_ATTR_IP6_DADDR;
	addattr_l(&req.n, 1024, peer_attr, &p->peer_ip.data, p->peer_ip.bytelen);

	if (p->encap == L2TP_ENCAPTYPE_UDP) {
		addattr16(&req.n, 1024, L2TP_ATTR_UDP_SPORT, p->local_udp_port);
		addattr16(&req.n, 1024, L2TP_ATTR_UDP_DPORT, p->peer_udp_port);
	}

	if (rtnl_talk(&genl_rth, &req.n, 0, 0, NULL) < 0)
		return -2;

	return 0;
}
