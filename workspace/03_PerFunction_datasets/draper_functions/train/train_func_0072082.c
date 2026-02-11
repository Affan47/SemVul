xgene_enet_rx_frame(struct xgene_enet_desc_ring *rx_ring,
			       struct xgene_enet_raw_desc *raw_desc)
{
	struct net_device *ndev;
	struct xgene_enet_pdata *pdata;
	struct device *dev;
	struct xgene_enet_desc_ring *buf_pool;
	u32 datalen, skb_index;
	struct sk_buff *skb;
	u8 status;
	int ret = 0;

	ndev = rx_ring->ndev;
	pdata = netdev_priv(ndev);
	dev = ndev_to_dev(rx_ring->ndev);
	buf_pool = rx_ring->buf_pool;

	dma_unmap_single(dev, GET_VAL(DATAADDR, le64_to_cpu(raw_desc->m1)),
			 XGENE_ENET_MAX_MTU, DMA_FROM_DEVICE);
	skb_index = GET_VAL(USERINFO, le64_to_cpu(raw_desc->m0));
	skb = buf_pool->rx_skb[skb_index];
	buf_pool->rx_skb[skb_index] = NULL;


	status = (GET_VAL(ELERR, le64_to_cpu(raw_desc->m0)) << LERR_LEN) ||
		  GET_VAL(LERR, le64_to_cpu(raw_desc->m0));
	if (unlikely(status > 2)) {
		dev_kfree_skb_any(skb);
		xgene_enet_parse_error(rx_ring, netdev_priv(rx_ring->ndev),
				       status);
		ret = -EIO;
		goto out;
	}


	datalen = GET_VAL(BUFDATALEN, le64_to_cpu(raw_desc->m1));
	datalen = (datalen & DATALEN_MASK) - 4;
	prefetch(skb->data - NET_IP_ALIGN);
	skb_put(skb, datalen);

	skb_checksum_none_assert(skb);
	skb->protocol = eth_type_trans(skb, ndev);
	if (likely((ndev->features & NETIF_F_IP_CSUM) &&
		   skb->protocol == htons(ETH_P_IP))) {
		xgene_enet_skip_csum(skb);
	}

	rx_ring->rx_packets++;
	rx_ring->rx_bytes += datalen;
	napi_gro_receive(&rx_ring->napi, skb);
out:
	if (--rx_ring->nbufpool == 0) {
		ret = xgene_enet_refill_bufpool(buf_pool, NUM_BUFPOOL);
		rx_ring->nbufpool = NUM_BUFPOOL;
	}

	return ret;
}
