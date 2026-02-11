irda_usb_net_timeout(struct net_device *netdev)
{
	unsigned long flags;
	struct irda_usb_cb *self = netdev_priv(netdev);
	struct urb *urb;
	int	done = 0;

	pr_debug("%s(), Network layer thinks we timed out!\n", __func__);
	IRDA_ASSERT(self != NULL, return;);


	spin_lock_irqsave(&self->lock, flags);


	if (!self->present) {
		net_warn_ratelimited("%s(), device not present!\n", __func__);
		netif_stop_queue(netdev);
		spin_unlock_irqrestore(&self->lock, flags);
		return;
	}


	urb = self->speed_urb;
	if (urb->status != 0) {
		pr_debug("%s: Speed change timed out, urb->status=%d, urb->transfer_flags=0x%04X\n",
			 netdev->name, urb->status, urb->transfer_flags);

		switch (urb->status) {
		case -EINPROGRESS:
			usb_unlink_urb(urb);


			done = 1;
			break;
		case -ECONNRESET:
		case -ENOENT:
		default:
			urb->status = 0;
			netif_wake_queue(self->netdev);
			done = 1;
			break;
		}
	}


	urb = self->tx_urb;
	if (urb->status != 0) {
		struct sk_buff *skb = urb->context;

		pr_debug("%s: Tx timed out, urb->status=%d, urb->transfer_flags=0x%04X\n",
			 netdev->name, urb->status, urb->transfer_flags);


		netdev->stats.tx_errors++;

#ifdef IU_BUG_KICK_TIMEOUT

		if(self->new_speed == -1)
			self->new_speed = self->speed;
		if(self->new_xbofs == -1)
			self->new_xbofs = self->xbofs;
		irda_usb_change_speed_xbofs(self);
#endif

		switch (urb->status) {
		case -EINPROGRESS:
			usb_unlink_urb(urb);


			done = 1;
			break;
		case -ECONNRESET:
		case -ENOENT:
		default:
			if(skb != NULL) {
				dev_kfree_skb_any(skb);
				urb->context = NULL;
			}
			urb->status = 0;
			netif_wake_queue(self->netdev);
			done = 1;
			break;
		}
	}
	spin_unlock_irqrestore(&self->lock, flags);


}
