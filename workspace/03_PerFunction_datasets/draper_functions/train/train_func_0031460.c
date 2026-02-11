netlink_neigh_request(struct nlmsghdr *msg)
{
	struct ndmsg *ndm = NLMSG_DATA(msg);
	struct rtattr *rta[NDA_MAX+1];
	struct nhrp_peer *peer;
	struct nhrp_address addr;
	struct nhrp_interface *iface;
	char tmp[64];

	netlink_parse_rtattr(rta, NDA_MAX, NDA_RTA(ndm), NDA_PAYLOAD(msg));
	if (rta[NDA_DST] == NULL)
		return;

	iface = nhrp_interface_get_by_index(ndm->ndm_ifindex, 0);
	if (iface == NULL)
		return;

	nhrp_address_set(&addr, ndm->ndm_family,
			 RTA_PAYLOAD(rta[NDA_DST]),
			 RTA_DATA(rta[NDA_DST]));

	nhrp_debug("NL-ARP(%s) who-has %s",
		   iface->name, nhrp_address_format(&addr, sizeof(tmp), tmp));

	peer = nhrp_peer_route(iface, &addr, 0, ~BIT(NHRP_PEER_TYPE_LOCAL_ROUTE));
	if (peer == NULL)
		return;

	if (peer->flags & NHRP_PEER_FLAG_UP)
		kernel_inject_neighbor(&addr, &peer->next_hop_address, iface);

	if (peer->next_hop_address.type != PF_UNSPEC &&
	    nhrp_address_cmp(&addr, &peer->protocol_address) != 0)
		nhrp_peer_traffic_indication(iface, peer->afnum, &addr);
}
