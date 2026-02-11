find_route_ipv4(struct flowi4 *fl4,
				      __be32 saddr, __be32 daddr,
				      __be16 sport, __be16 dport, u8 tos)
{
	struct rtable *rt;

	rt = ip_route_output_ports(&init_net, fl4, NULL, daddr, saddr,
				   dport, sport, IPPROTO_TCP, tos, 0);
	if (IS_ERR(rt))
		return NULL;

	return rt;
}
