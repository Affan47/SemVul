vxlan_xmit_skb(struct rtable *rt, struct sock *sk, struct sk_buff *skb,
			  __be32 src, __be32 dst, __u8 tos, __u8 ttl, __be16 df,
			  __be16 src_port, __be16 dst_port, __be32 vni,
			  struct vxlan_metadata *md, bool xnet, u32 vxflags)
{
	struct vxlanhdr *vxh;
	int min_headroom;
	int err;
	bool udp_sum = !!(vxflags & VXLAN_F_UDP_CSUM);
	int type = udp_sum ? SKB_GSO_UDP_TUNNEL_CSUM : SKB_GSO_UDP_TUNNEL;
	u16 hdrlen = sizeof(struct vxlanhdr);

	if ((vxflags & VXLAN_F_REMCSUM_TX) &&
	    skb->ip_summed == CHECKSUM_PARTIAL) {
		int csum_start = skb_checksum_start_offset(skb);

		if (csum_start <= VXLAN_MAX_REMCSUM_START &&
		    !(csum_start & VXLAN_RCO_SHIFT_MASK) &&
		    (skb->csum_offset == offsetof(struct udphdr, check) ||
		     skb->csum_offset == offsetof(struct tcphdr, check))) {
			udp_sum = false;
			type |= SKB_GSO_TUNNEL_REMCSUM;
		}
	}

	min_headroom = LL_RESERVED_SPACE(rt->dst.dev) + rt->dst.header_len
			+ VXLAN_HLEN + sizeof(struct iphdr)
			+ (skb_vlan_tag_present(skb) ? VLAN_HLEN : 0);


	err = skb_cow_head(skb, min_headroom);
	if (unlikely(err)) {
		kfree_skb(skb);
		return err;
	}

	skb = vlan_hwaccel_push_inside(skb);
	if (WARN_ON(!skb))
		return -ENOMEM;

	skb = iptunnel_handle_offloads(skb, udp_sum, type);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	vxh = (struct vxlanhdr *) __skb_push(skb, sizeof(*vxh));
	vxh->vx_flags = htonl(VXLAN_HF_VNI);
	vxh->vx_vni = vni;

	if (type & SKB_GSO_TUNNEL_REMCSUM) {
		u32 data = (skb_checksum_start_offset(skb) - hdrlen) >>
			   VXLAN_RCO_SHIFT;

		if (skb->csum_offset == offsetof(struct udphdr, check))
			data |= VXLAN_RCO_UDP;

		vxh->vx_vni |= htonl(data);
		vxh->vx_flags |= htonl(VXLAN_HF_RCO);

		if (!skb_is_gso(skb)) {
			skb->ip_summed = CHECKSUM_NONE;
			skb->encapsulation = 0;
		}
	}

	if (vxflags & VXLAN_F_GBP)
		vxlan_build_gbp_hdr(vxh, vxflags, md);

	skb_set_inner_protocol(skb, htons(ETH_P_TEB));

	return udp_tunnel_xmit_skb(rt, sk, skb, src, dst, tos,
				   ttl, df, src_port, dst_port, xnet,
				   !(vxflags & VXLAN_F_UDP_CSUM));
}
