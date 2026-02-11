irda_usb_receive(struct urb *urb)
{
	struct sk_buff *skb = (struct sk_buff *) urb->context;
	struct irda_usb_cb *self;
	struct irda_skb_cb *cb;
	struct sk_buff *newskb;
	struct sk_buff *dataskb;
	struct urb *next_urb;
	unsigned int len, docopy;

	pr_debug("%s(), len=%d\n", __func__, urb->actual_length);


	cb = (struct irda_skb_cb *) skb->cb;
	IRDA_ASSERT(cb != NULL, return;);
	self = (struct irda_usb_cb *) cb->context;
	IRDA_ASSERT(self != NULL, return;);


	if ((!self->netopen) || (!self->present)) {
		pr_debug("%s(), Network is gone!\n", __func__);

		return;
	}


	if (urb->status != 0) {
		switch (urb->status) {
		case -EILSEQ:
			self->netdev->stats.rx_crc_errors++;


		case -ECONNRESET:


		case -ESHUTDOWN:

		case -ETIME:

		default:
			self->netdev->stats.rx_errors++;
			pr_debug("%s(), RX status %d, transfer_flags 0x%04X\n",
				 __func__, urb->status, urb->transfer_flags);
			break;
		}


		self->rx_defer_timer.function = irda_usb_rx_defer_expired;
		self->rx_defer_timer.data = (unsigned long) urb;
		mod_timer(&self->rx_defer_timer,
			  jiffies + msecs_to_jiffies(10));

		return;
	}


	if (urb->actual_length <= self->header_length) {
		net_warn_ratelimited("%s(), empty frame!\n", __func__);
		goto done;
	}


	self->stamp = ktime_get();


	docopy = (urb->actual_length < IRDA_RX_COPY_THRESHOLD);


	if (self->capability & IUC_STIR421X)
		newskb = dev_alloc_skb(docopy ? urb->actual_length :
				       IRDA_SKB_MAX_MTU +
				       USB_IRDA_STIR421X_HEADER);
	else
		newskb = dev_alloc_skb(docopy ? urb->actual_length :
				       IRDA_SKB_MAX_MTU);

	if (!newskb)  {
		self->netdev->stats.rx_dropped++;


		goto done;
	}


	if(docopy) {

		skb_copy_from_linear_data(skb, newskb->data, urb->actual_length);

		dataskb = newskb;


	} else {

		dataskb = skb;

		skb = newskb;
	}


	skb_put(dataskb, urb->actual_length);
	skb_pull(dataskb, self->header_length);


	dataskb->dev = self->netdev;
	skb_reset_mac_header(dataskb);
	dataskb->protocol = htons(ETH_P_IRDA);
	len = dataskb->len;
	netif_rx(dataskb);


	self->netdev->stats.rx_bytes += len;
	self->netdev->stats.rx_packets++;

done:


	next_urb = self->idle_rx_urb;


	urb->context = NULL;
	self->idle_rx_urb = urb;


	irda_usb_submit(self, skb, next_urb);
}
