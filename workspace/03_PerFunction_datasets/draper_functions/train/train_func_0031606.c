vmxnet3_parse_and_copy_hdr(struct sk_buff *skb, struct vmxnet3_tx_queue *tq,
			   struct vmxnet3_tx_ctx *ctx,
			   struct vmxnet3_adapter *adapter)
{
	struct Vmxnet3_TxDataDesc *tdd;
	u8 protocol = 0;

	if (ctx->mss) {
		ctx->eth_ip_hdr_size = skb_transport_offset(skb);
		ctx->l4_hdr_size = tcp_hdrlen(skb);
		ctx->copy_size = ctx->eth_ip_hdr_size + ctx->l4_hdr_size;
	} else {
		if (skb->ip_summed == CHECKSUM_PARTIAL) {
			ctx->eth_ip_hdr_size = skb_checksum_start_offset(skb);

			if (ctx->ipv4) {
				const struct iphdr *iph = ip_hdr(skb);

				protocol = iph->protocol;
			} else if (ctx->ipv6) {
				const struct ipv6hdr *ipv6h = ipv6_hdr(skb);

				protocol = ipv6h->nexthdr;
			}

			switch (protocol) {
			case IPPROTO_TCP:
				ctx->l4_hdr_size = tcp_hdrlen(skb);
				break;
			case IPPROTO_UDP:
				ctx->l4_hdr_size = sizeof(struct udphdr);
				break;
			default:
				ctx->l4_hdr_size = 0;
				break;
			}

			ctx->copy_size = min(ctx->eth_ip_hdr_size +
					 ctx->l4_hdr_size, skb->len);
		} else {
			ctx->eth_ip_hdr_size = 0;
			ctx->l4_hdr_size = 0;

			ctx->copy_size = min((unsigned int)VMXNET3_HDR_COPY_SIZE
					     , skb_headlen(skb));
		}

		if (skb->len <= VMXNET3_HDR_COPY_SIZE)
			ctx->copy_size = skb->len;


		if (unlikely(!pskb_may_pull(skb, ctx->copy_size)))
			goto err;
	}

	if (unlikely(ctx->copy_size > VMXNET3_HDR_COPY_SIZE)) {
		tq->stats.oversized_hdr++;
		ctx->copy_size = 0;
		return 0;
	}

	tdd = tq->data_ring.base + tq->tx_ring.next2fill;

	memcpy(tdd->data, skb->data, ctx->copy_size);
	netdev_dbg(adapter->netdev,
		"copy %u bytes to dataRing[%u]\n",
		ctx->copy_size, tq->tx_ring.next2fill);
	return 1;

err:
	return -1;
}
