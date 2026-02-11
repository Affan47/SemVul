p54u_init_urbs(struct ieee80211_hw *dev)
{
	struct p54u_priv *priv = dev->priv;
	struct urb *entry = NULL;
	struct sk_buff *skb;
	struct p54u_rx_info *info;
	int ret = 0;

	while (skb_queue_len(&priv->rx_queue) < 32) {
		skb = __dev_alloc_skb(priv->common.rx_mtu + 32, GFP_KERNEL);
		if (!skb) {
			ret = -ENOMEM;
			goto err;
		}
		entry = usb_alloc_urb(0, GFP_KERNEL);
		if (!entry) {
			ret = -ENOMEM;
			goto err;
		}

		usb_fill_bulk_urb(entry, priv->udev,
				  usb_rcvbulkpipe(priv->udev, P54U_PIPE_DATA),
				  skb_tail_pointer(skb),
				  priv->common.rx_mtu + 32, p54u_rx_cb, skb);
		info = (struct p54u_rx_info *) skb->cb;
		info->urb = entry;
		info->dev = dev;
		skb_queue_tail(&priv->rx_queue, skb);

		usb_anchor_urb(entry, &priv->submitted);
		ret = usb_submit_urb(entry, GFP_KERNEL);
		if (ret) {
			skb_unlink(skb, &priv->rx_queue);
			usb_unanchor_urb(entry);
			goto err;
		}
		usb_free_urb(entry);
		entry = NULL;
	}

	return 0;

 err:
	usb_free_urb(entry);
	kfree_skb(skb);
	p54u_free_urbs(dev);
	return ret;
}
