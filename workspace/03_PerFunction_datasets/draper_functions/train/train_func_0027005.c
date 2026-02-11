irda_usb_net_close(struct net_device *netdev)
{
	struct irda_usb_cb *self;
	int	i;

	IRDA_ASSERT(netdev != NULL, return -1;);
	self = netdev_priv(netdev);
	IRDA_ASSERT(self != NULL, return -1;);


	self->netopen = 0;


	netif_stop_queue(netdev);


	del_timer(&self->rx_defer_timer);


	for (i = 0; i < self->max_rx_urb; i++) {
		struct urb *urb = self->rx_urb[i];
		struct sk_buff *skb = (struct sk_buff *) urb->context;

		usb_kill_urb(urb);

		if(skb) {
			dev_kfree_skb(skb);
			urb->context = NULL;
		}
	}

	usb_kill_urb(self->tx_urb);
	usb_kill_urb(self->speed_urb);


	if (self->irlap)
		irlap_close(self->irlap);
	self->irlap = NULL;

	return 0;
}
