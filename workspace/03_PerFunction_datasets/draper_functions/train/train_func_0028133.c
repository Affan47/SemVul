find_route6(struct c4iw_dev *dev, __u8 *local_ip,
				     __u8 *peer_ip, __be16 local_port,
				     __be16 peer_port, u8 tos,
				     __u32 sin6_scope_id)
{
	struct dst_entry *dst = NULL;

	if (IS_ENABLED(CONFIG_IPV6)) {
		struct flowi6 fl6;

		memset(&fl6, 0, sizeof(fl6));
		memcpy(&fl6.daddr, peer_ip, 16);
		memcpy(&fl6.saddr, local_ip, 16);
		if (ipv6_addr_type(&fl6.daddr) & IPV6_ADDR_LINKLOCAL)
			fl6.flowi6_oif = sin6_scope_id;
		dst = ip6_route_output(&init_net, NULL, &fl6);
		if (!dst)
			goto out;
		if (!our_interface(dev, ip6_dst_idev(dst)->dev) &&
		    !(ip6_dst_idev(dst)->dev->flags & IFF_LOOPBACK)) {
			dst_release(dst);
			dst = NULL;
		}
	}

out:
	return dst;
}
