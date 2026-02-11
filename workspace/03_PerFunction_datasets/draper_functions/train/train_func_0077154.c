vxlan_udp_encap_recv(struct sock *sk, struct sk_buff *skb)
{
	struct metadata_dst *tun_dst = NULL;
	struct vxlan_sock *vs;
	struct vxlanhdr *vxh;
	u32 flags, vni;
	struct vxlan_metadata _md;
	struct vxlan_metadata *md = &_md;


	if (!pskb_may_pull(skb, VXLAN_HLEN))
		goto drop;

	vxh = (struct vxlanhdr *)(udp_hdr(skb) + 1);
	flags = ntohl(vxh->vx_flags);
	vni = ntohl(vxh->vx_vni);

	if (flags & VXLAN_HF_VNI) {
		flags &= ~VXLAN_HF_VNI;
	} else {

		goto bad_flags;
	}

	if (iptunnel_pull_header(skb, VXLAN_HLEN, htons(ETH_P_TEB)))
		goto drop;
	vxh = (struct vxlanhdr *)(udp_hdr(skb) + 1);

	vs = rcu_dereference_sk_user_data(sk);
	if (!vs)
		goto drop;

	if ((flags & VXLAN_HF_RCO) && (vs->flags & VXLAN_F_REMCSUM_RX)) {
		vxh = vxlan_remcsum(skb, vxh, sizeof(struct vxlanhdr), vni,
				    !!(vs->flags & VXLAN_F_REMCSUM_NOPARTIAL));
		if (!vxh)
			goto drop;

		flags &= ~VXLAN_HF_RCO;
		vni &= VXLAN_VNI_MASK;
	}

	if (vxlan_collect_metadata(vs)) {
		tun_dst = udp_tun_rx_dst(skb, vxlan_get_sk_family(vs), TUNNEL_KEY,
					 cpu_to_be64(vni >> 8), sizeof(*md));

		if (!tun_dst)
			goto drop;

		md = ip_tunnel_info_opts(&tun_dst->u.tun_info);
	} else {
		memset(md, 0, sizeof(*md));
	}


	if ((flags & VXLAN_HF_GBP) && (vs->flags & VXLAN_F_GBP)) {
		struct vxlanhdr_gbp *gbp;

		gbp = (struct vxlanhdr_gbp *)vxh;
		md->gbp = ntohs(gbp->policy_id);

		if (tun_dst) {
			tun_dst->u.tun_info.key.tun_flags |= TUNNEL_VXLAN_OPT;
			tun_dst->u.tun_info.options_len = sizeof(*md);
		}

		if (gbp->dont_learn)
			md->gbp |= VXLAN_GBP_DONT_LEARN;

		if (gbp->policy_applied)
			md->gbp |= VXLAN_GBP_POLICY_APPLIED;

		flags &= ~VXLAN_GBP_USED_BITS;
	}

	if (flags || vni & ~VXLAN_VNI_MASK) {


		goto bad_flags;
	}

	vxlan_rcv(vs, skb, md, vni >> 8, tun_dst);
	return 0;

drop:

	kfree_skb(skb);
	return 0;

bad_flags:
	netdev_dbg(skb->dev, "invalid vxlan flags=%#x vni=%#x\n",
		   ntohl(vxh->vx_flags), ntohl(vxh->vx_vni));
	goto drop;
}
