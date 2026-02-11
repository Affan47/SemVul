fjn_start_xmit(struct sk_buff *skb,
					struct net_device *dev)
{
    struct local_info *lp = netdev_priv(dev);
    unsigned int ioaddr = dev->base_addr;
    short length = skb->len;

    if (length < ETH_ZLEN)
    {
    	if (skb_padto(skb, ETH_ZLEN))
    		return NETDEV_TX_OK;
    	length = ETH_ZLEN;
    }

    netif_stop_queue(dev);

    {
	unsigned char *buf = skb->data;

	if (length > ETH_FRAME_LEN) {
	    netdev_notice(dev, "Attempting to send a large packet (%d bytes)\n",
			  length);
	    return NETDEV_TX_BUSY;
	}

	netdev_dbg(dev, "Transmitting a packet of length %lu\n",
		   (unsigned long)skb->len);
	dev->stats.tx_bytes += skb->len;


	outw(0x0000, ioaddr + TX_INTR);


	udelay(1);

	outw(length, ioaddr + DATAPORT);
	outsw(ioaddr + DATAPORT, buf, (length + 1) >> 1);

	lp->tx_queue++;
	lp->tx_queue_len += ((length+3) & ~1);

	if (lp->tx_started == 0) {

	    outb(DO_TX | lp->tx_queue, ioaddr + TX_START);
	    lp->sent = lp->tx_queue ;
	    lp->tx_queue = 0;
	    lp->tx_queue_len = 0;
	    lp->tx_started = 1;
	    netif_start_queue(dev);
	} else {
	    if( sram_config == 0 ) {
		if (lp->tx_queue_len < (4096 - (ETH_FRAME_LEN +2)) )

		    netif_start_queue(dev);
	    } else {
		if (lp->tx_queue_len < (8192 - (ETH_FRAME_LEN +2)) &&
						lp->tx_queue < 127 )

		    netif_start_queue(dev);
	    }
	}


	outb(D_TX_INTR, ioaddr + TX_INTR);
	outb(D_RX_INTR, ioaddr + RX_INTR);
    }
    dev_kfree_skb (skb);

    return NETDEV_TX_OK;
}
