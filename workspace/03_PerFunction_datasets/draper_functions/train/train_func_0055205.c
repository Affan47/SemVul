macvtap_put_user(struct macvtap_queue *q,
				const struct sk_buff *skb,
				struct iov_iter *iter)
{
	int ret;
	int vnet_hdr_len = 0;
	int vlan_offset = 0;
	int total;

	if (q->flags & IFF_VNET_HDR) {
		struct virtio_net_hdr vnet_hdr;
		vnet_hdr_len = READ_ONCE(q->vnet_hdr_sz);
		if (iov_iter_count(iter) < vnet_hdr_len)
			return -EINVAL;

		macvtap_skb_to_vnet_hdr(q, skb, &vnet_hdr);

		if (copy_to_iter(&vnet_hdr, sizeof(vnet_hdr), iter) !=
		    sizeof(vnet_hdr))
			return -EFAULT;

		iov_iter_advance(iter, vnet_hdr_len - sizeof(vnet_hdr));
	}
	total = vnet_hdr_len;
	total += skb->len;

	if (skb_vlan_tag_present(skb)) {
		struct {
			__be16 h_vlan_proto;
			__be16 h_vlan_TCI;
		} veth;
		veth.h_vlan_proto = skb->vlan_proto;
		veth.h_vlan_TCI = htons(skb_vlan_tag_get(skb));

		vlan_offset = offsetof(struct vlan_ethhdr, h_vlan_proto);
		total += VLAN_HLEN;

		ret = skb_copy_datagram_iter(skb, 0, iter, vlan_offset);
		if (ret || !iov_iter_count(iter))
			goto done;

		ret = copy_to_iter(&veth, sizeof(veth), iter);
		if (ret != sizeof(veth) || !iov_iter_count(iter))
			goto done;
	}

	ret = skb_copy_datagram_iter(skb, vlan_offset, iter,
				     skb->len - vlan_offset);

done:
	return ret ? ret : total;
}
