slic_rcvqueue_fill(struct adapter *adapter)
{
	void *paddr;
	u32 paddrl;
	u32 paddrh;
	struct slic_rcvqueue *rcvq = &adapter->rcvqueue;
	int i = 0;
	struct device *dev = &adapter->netdev->dev;

	while (i < SLIC_RCVQ_FILLENTRIES) {
		struct slic_rcvbuf *rcvbuf;
		struct sk_buff *skb;
#ifdef KLUDGE_FOR_4GB_BOUNDARY
retry_rcvqfill:
#endif
		skb = alloc_skb(SLIC_RCVQ_RCVBUFSIZE, GFP_ATOMIC);
		if (skb) {
			paddr = (void *)(unsigned long)
				pci_map_single(adapter->pcidev,
					       skb->data,
					       SLIC_RCVQ_RCVBUFSIZE,
					       PCI_DMA_FROMDEVICE);
			paddrl = SLIC_GET_ADDR_LOW(paddr);
			paddrh = SLIC_GET_ADDR_HIGH(paddr);

			skb->len = SLIC_RCVBUF_HEADSIZE;
			rcvbuf = (struct slic_rcvbuf *)skb->head;
			rcvbuf->status = 0;
			skb->next = NULL;
#ifdef KLUDGE_FOR_4GB_BOUNDARY
			if (paddrl == 0) {
				dev_err(dev, "%s: LOW 32bits PHYSICAL ADDRESS == 0\n",
					__func__);
				dev_err(dev, "skb[%p] PROBLEM\n", skb);
				dev_err(dev, "         skbdata[%p]\n",
						skb->data);
				dev_err(dev, "         skblen[%x]\n", skb->len);
				dev_err(dev, "         paddr[%p]\n", paddr);
				dev_err(dev, "         paddrl[%x]\n", paddrl);
				dev_err(dev, "         paddrh[%x]\n", paddrh);
				dev_err(dev, "         rcvq->head[%p]\n",
						rcvq->head);
				dev_err(dev, "         rcvq->tail[%p]\n",
						rcvq->tail);
				dev_err(dev, "         rcvq->count[%x]\n",
						rcvq->count);
				dev_err(dev, "SKIP THIS SKB!!!!!!!!\n");
				goto retry_rcvqfill;
			}
#else
			if (paddrl == 0) {
				dev_err(dev, "%s: LOW 32bits PHYSICAL ADDRESS == 0\n",
					__func__);
				dev_err(dev, "skb[%p] PROBLEM\n", skb);
				dev_err(dev, "         skbdata[%p]\n",
						skb->data);
				dev_err(dev, "         skblen[%x]\n", skb->len);
				dev_err(dev, "         paddr[%p]\n", paddr);
				dev_err(dev, "         paddrl[%x]\n", paddrl);
				dev_err(dev, "         paddrh[%x]\n", paddrh);
				dev_err(dev, "         rcvq->head[%p]\n",
						rcvq->head);
				dev_err(dev, "         rcvq->tail[%p]\n",
						rcvq->tail);
				dev_err(dev, "         rcvq->count[%x]\n",
						rcvq->count);
				dev_err(dev, "GIVE TO CARD ANYWAY\n");
			}
#endif
			if (paddrh == 0) {
				slic_reg32_write(&adapter->slic_regs->slic_hbar,
						 (u32)paddrl, DONT_FLUSH);
			} else {
				slic_reg64_write(adapter,
					&adapter->slic_regs->slic_hbar64,
					paddrl,
					&adapter->slic_regs->slic_addr_upper,
					paddrh, DONT_FLUSH);
			}
			if (rcvq->head)
				rcvq->tail->next = skb;
			else
				rcvq->head = skb;
			rcvq->tail = skb;
			rcvq->count++;
			i++;
		} else {
			dev_err(&adapter->netdev->dev,
				"slic_rcvqueue_fill could only get [%d] skbuffs\n",
				i);
			break;
		}
	}
	return i;
}
