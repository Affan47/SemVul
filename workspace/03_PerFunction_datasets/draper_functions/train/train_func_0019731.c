rtl8169_xmit_frags(struct rtl8169_private *tp, struct sk_buff *skb,
			      u32 *opts)
{
	struct skb_shared_info *info = skb_shinfo(skb);
	unsigned int cur_frag, entry;
	struct TxDesc *uninitialized_var(txd);
	struct device *d = &tp->pci_dev->dev;

	entry = tp->cur_tx;
	for (cur_frag = 0; cur_frag < info->nr_frags; cur_frag++) {
		const skb_frag_t *frag = info->frags + cur_frag;
		dma_addr_t mapping;
		u32 status, len;
		void *addr;

		entry = (entry + 1) % NUM_TX_DESC;

		txd = tp->TxDescArray + entry;
		len = skb_frag_size(frag);
		addr = skb_frag_address(frag);
		mapping = dma_map_single(d, addr, len, DMA_TO_DEVICE);
		if (unlikely(dma_mapping_error(d, mapping))) {
			if (net_ratelimit())
				netif_err(tp, drv, tp->dev,
					  "Failed to map TX fragments DMA!\n");
			goto err_out;
		}


		status = opts[0] | len |
			(RingEnd * !((entry + 1) % NUM_TX_DESC));

		txd->opts1 = cpu_to_le32(status);
		txd->opts2 = cpu_to_le32(opts[1]);
		txd->addr = cpu_to_le64(mapping);

		tp->tx_skb[entry].len = len;
	}

	if (cur_frag) {
		tp->tx_skb[entry].skb = skb;
		txd->opts1 |= cpu_to_le32(LastFrag);
	}

	return cur_frag;

err_out:
	rtl8169_tx_clear_range(tp, tp->cur_tx + 1, cur_frag);
	return -EIO;
}
