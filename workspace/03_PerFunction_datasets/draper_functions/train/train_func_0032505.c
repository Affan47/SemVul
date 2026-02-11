isr_rx(struct ipw2100_priv *priv, int i,
			  struct libipw_rx_stats *stats)
{
	struct net_device *dev = priv->net_dev;
	struct ipw2100_status *status = &priv->status_queue.drv[i];
	struct ipw2100_rx_packet *packet = &priv->rx_buffers[i];

	IPW_DEBUG_RX("Handler...\n");

	if (unlikely(status->frame_size > skb_tailroom(packet->skb))) {
		IPW_DEBUG_INFO("%s: frame_size (%u) > skb_tailroom (%u)!"
			       "  Dropping.\n",
			       dev->name,
			       status->frame_size, skb_tailroom(packet->skb));
		dev->stats.rx_errors++;
		return;
	}

	if (unlikely(!netif_running(dev))) {
		dev->stats.rx_errors++;
		priv->wstats.discard.misc++;
		IPW_DEBUG_DROP("Dropping packet while interface is not up.\n");
		return;
	}

	if (unlikely(priv->ieee->iw_mode != IW_MODE_MONITOR &&
		     !(priv->status & STATUS_ASSOCIATED))) {
		IPW_DEBUG_DROP("Dropping packet while not associated.\n");
		priv->wstats.discard.misc++;
		return;
	}

	pci_unmap_single(priv->pci_dev,
			 packet->dma_addr,
			 sizeof(struct ipw2100_rx), PCI_DMA_FROMDEVICE);

	skb_put(packet->skb, status->frame_size);

#ifdef IPW2100_RX_DEBUG


	skb_copy_from_linear_data(packet->skb, packet_data,
				  min_t(u32, status->frame_size,
					     IPW_RX_NIC_BUFFER_LENGTH));
#endif

	if (!libipw_rx(priv->ieee, packet->skb, stats)) {
#ifdef IPW2100_RX_DEBUG
		IPW_DEBUG_DROP("%s: Non consumed packet:\n",
			       dev->name);
		printk_buf(IPW_DL_DROP, packet_data, status->frame_size);
#endif
		dev->stats.rx_errors++;


		dev_kfree_skb_any(packet->skb);
		packet->skb = NULL;
	}


	if (unlikely(ipw2100_alloc_skb(priv, packet))) {
		printk(KERN_WARNING DRV_NAME ": "
		       "%s: Unable to allocate SKB onto RBD ring - disabling "
		       "adapter.\n", dev->name);

		IPW_DEBUG_INFO("TODO: Shutdown adapter...\n");
	}


	priv->rx_queue.drv[i].host_addr = packet->dma_addr;
}
