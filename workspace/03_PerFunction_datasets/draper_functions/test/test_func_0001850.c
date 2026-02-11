rx_process(struct lan78xx_net *dev, struct sk_buff *skb)
{
	if (!lan78xx_rx(dev, skb)) {
		dev->net->stats.rx_errors++;
		goto done;
	}

	if (skb->len) {
		lan78xx_skb_return(dev, skb);
		return;
	}

	netif_dbg(dev, rx_err, dev->net, "drop\n");
	dev->net->stats.rx_errors++;
done:
	skb_queue_tail(&dev->done, skb);
}
