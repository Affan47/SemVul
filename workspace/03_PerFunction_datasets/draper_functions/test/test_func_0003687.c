mpt_lan_close(struct net_device *dev)
{
	struct mpt_lan_priv *priv = netdev_priv(dev);
	MPT_ADAPTER *mpt_dev = priv->mpt_dev;
	unsigned long timeout;
	int i;

	dlprintk((KERN_INFO MYNAM ": mpt_lan_close called\n"));

	mpt_event_deregister(LanCtx);

	dlprintk((KERN_INFO MYNAM ":lan_close: Posted %d buckets "
		  "since driver was loaded, %d still out\n",
		  priv->total_posted,atomic_read(&priv->buckets_out)));

	netif_stop_queue(dev);

	mpt_lan_reset(dev);

	timeout = jiffies + 2 * HZ;
	while (atomic_read(&priv->buckets_out) && time_before(jiffies, timeout))
		schedule_timeout_interruptible(1);

	for (i = 0; i < priv->max_buckets_out; i++) {
		if (priv->RcvCtl[i].skb != NULL) {
			dlprintk((KERN_INFO MYNAM "/lan_close: bucket %05x "
				  "is still out\n", i));
			pci_unmap_single(mpt_dev->pcidev, priv->RcvCtl[i].dma,
					 priv->RcvCtl[i].len,
					 PCI_DMA_FROMDEVICE);
			dev_kfree_skb(priv->RcvCtl[i].skb);
		}
	}

	kfree(priv->RcvCtl);
	kfree(priv->mpt_rxfidx);

	for (i = 0; i < priv->tx_max_out; i++) {
		if (priv->SendCtl[i].skb != NULL) {
			pci_unmap_single(mpt_dev->pcidev, priv->SendCtl[i].dma,
					 priv->SendCtl[i].len,
					 PCI_DMA_TODEVICE);
			dev_kfree_skb(priv->SendCtl[i].skb);
		}
	}

	kfree(priv->SendCtl);
	kfree(priv->mpt_txfidx);

	atomic_set(&priv->buckets_out, 0);

	printk(KERN_INFO MYNAM ": %s/%s: interface down & inactive\n",
			IOC_AND_NETDEV_NAMES_s_s(dev));

	return 0;
}
