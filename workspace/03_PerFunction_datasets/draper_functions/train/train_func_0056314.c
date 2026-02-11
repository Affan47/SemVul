rtl8188eu_free_recv_priv(struct adapter *padapter)
{
	int	i;
	struct recv_buf	*precvbuf;
	struct recv_priv	*precvpriv = &padapter->recvpriv;

	precvbuf = (struct recv_buf *)precvpriv->precv_buf;

	for (i = 0; i < NR_RECVBUFF; i++) {
		usb_free_urb(precvbuf->purb);
		precvbuf++;
	}

	kfree(precvpriv->pallocated_recv_buf);

	if (skb_queue_len(&precvpriv->rx_skb_queue))
		DBG_88E(KERN_WARNING "rx_skb_queue not empty\n");
	skb_queue_purge(&precvpriv->rx_skb_queue);


	if (skb_queue_len(&precvpriv->free_recv_skb_queue))
		DBG_88E(KERN_WARNING "free_recv_skb_queue not empty, %d\n",
				skb_queue_len(&precvpriv->free_recv_skb_queue));

	skb_queue_purge(&precvpriv->free_recv_skb_queue);
}
