mpt_lan_receive_post_free(struct net_device *dev,
			  LANReceivePostReply_t *pRecvRep)
{
	struct mpt_lan_priv *priv = netdev_priv(dev);
	MPT_ADAPTER *mpt_dev = priv->mpt_dev;
	unsigned long flags;
	struct sk_buff *skb;
	u32 ctx;
	int count;
	int i;

	count = pRecvRep->NumberOfContexts;

	dlprintk((KERN_INFO MYNAM "/receive_post_reply: "
		  "IOC returned %d buckets, freeing them...\n", count));

	spin_lock_irqsave(&priv->rxfidx_lock, flags);
	for (i = 0; i < count; i++) {
		ctx = le32_to_cpu(pRecvRep->BucketContext[i]);

		skb = priv->RcvCtl[ctx].skb;


		priv->RcvCtl[ctx].skb = NULL;
		pci_unmap_single(mpt_dev->pcidev, priv->RcvCtl[ctx].dma,
				 priv->RcvCtl[ctx].len, PCI_DMA_FROMDEVICE);
		dev_kfree_skb_any(skb);

		priv->mpt_rxfidx[++priv->mpt_rxfidx_tail] = ctx;
	}
	spin_unlock_irqrestore(&priv->rxfidx_lock, flags);

	atomic_sub(count, &priv->buckets_out);


	dlprintk((KERN_INFO MYNAM "@receive_post_reply: %d buckets "
		  "remaining, %d received back since sod.\n",
		  atomic_read(&priv->buckets_out), priv->total_received));
	return 0;
}
