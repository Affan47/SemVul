hix5hd2_rx(struct net_device *dev, int limit)
{
	struct hix5hd2_priv *priv = netdev_priv(dev);
	struct sk_buff *skb;
	struct hix5hd2_desc *desc;
	dma_addr_t addr;
	u32 start, end, num, pos, i, len;


	start = dma_cnt(readl_relaxed(priv->base + RX_BQ_RD_ADDR));

	end = dma_cnt(readl_relaxed(priv->base + RX_BQ_WR_ADDR));
	num = CIRC_CNT(end, start, RX_DESC_NUM);
	if (num > limit)
		num = limit;


	rmb();
	for (i = 0, pos = start; i < num; i++) {
		skb = priv->rx_skb[pos];
		if (unlikely(!skb)) {
			netdev_err(dev, "inconsistent rx_skb\n");
			break;
		}
		priv->rx_skb[pos] = NULL;

		desc = priv->rx_bq.desc + pos;
		len = (le32_to_cpu(desc->cmd) >> DESC_DATA_LEN_OFF) &
		       DESC_DATA_MASK;
		addr = le32_to_cpu(desc->buff_addr);
		dma_unmap_single(priv->dev, addr, MAC_MAX_FRAME_SIZE,
				 DMA_FROM_DEVICE);

		skb_put(skb, len);
		if (skb->len > MAC_MAX_FRAME_SIZE) {
			netdev_err(dev, "rcv len err, len = %d\n", skb->len);
			dev->stats.rx_errors++;
			dev->stats.rx_length_errors++;
			dev_kfree_skb_any(skb);
			goto next;
		}

		skb->protocol = eth_type_trans(skb, dev);
		napi_gro_receive(&priv->napi, skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
next:
		pos = dma_ring_incr(pos, RX_DESC_NUM);
	}

	if (pos != start)
		writel_relaxed(dma_byte(pos), priv->base + RX_BQ_RD_ADDR);

	hix5hd2_rx_refill(priv);

	return num;
}
