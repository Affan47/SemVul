rhine_skb_dma_init(struct net_device *dev,
				     struct rhine_skb_dma *sd)
{
	struct rhine_private *rp = netdev_priv(dev);
	struct device *hwdev = dev->dev.parent;
	const int size = rp->rx_buf_sz;

	sd->skb = netdev_alloc_skb(dev, size);
	if (!sd->skb)
		return -ENOMEM;

	sd->dma = dma_map_single(hwdev, sd->skb->data, size, DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(hwdev, sd->dma))) {
		netif_err(rp, drv, dev, "Rx DMA mapping failure\n");
		dev_kfree_skb_any(sd->skb);
		return -EIO;
	}

	return 0;
}
