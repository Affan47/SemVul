geneve_get_v4_rt(struct sk_buff *skb,
				       struct net_device *dev,
				       struct flowi4 *fl4,
				       struct ip_tunnel_info *info)
{
	struct geneve_dev *geneve = netdev_priv(dev);
	struct rtable *rt = NULL;
	__u8 tos;

	memset(fl4, 0, sizeof(*fl4));
	fl4->flowi4_mark = skb->mark;
	fl4->flowi4_proto = IPPROTO_UDP;

	if (info) {
		fl4->daddr = info->key.u.ipv4.dst;
		fl4->saddr = info->key.u.ipv4.src;
		fl4->flowi4_tos = RT_TOS(info->key.tos);
	} else {
		tos = geneve->tos;
		if (tos == 1) {
			const struct iphdr *iip = ip_hdr(skb);

			tos = ip_tunnel_get_dsfield(iip, skb);
		}

		fl4->flowi4_tos = RT_TOS(tos);
		fl4->daddr = geneve->remote.sin.sin_addr.s_addr;
	}

	rt = ip_route_output_key(geneve->net, fl4);
	if (IS_ERR(rt)) {
		netdev_dbg(dev, "no route to %pI4\n", &fl4->daddr);
		return ERR_PTR(-ENETUNREACH);
	}
	if (rt->dst.dev == dev) {
		netdev_dbg(dev, "circular route to %pI4\n", &fl4->daddr);
		ip_rt_put(rt);
		return ERR_PTR(-ELOOP);
	}
	return rt;
}
