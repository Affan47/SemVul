r8712_usb_read_port_complete(struct urb *purb)
{
	uint isevt, *pbuf;
	struct recv_buf	*precvbuf = (struct recv_buf *)purb->context;
	struct _adapter *padapter = (struct _adapter *)precvbuf->adapter;
	struct recv_priv *precvpriv = &padapter->recvpriv;

	if (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		return;
	if (purb->status == 0) {
		if ((purb->actual_length > (MAX_RECVBUF_SZ)) ||
		    (purb->actual_length < RXDESC_SIZE)) {
			precvbuf->reuse = true;
			r8712_read_port(padapter, precvpriv->ff_hwaddr, 0,
				  (unsigned char *)precvbuf);
		} else {
			precvbuf->transfer_len = purb->actual_length;
			pbuf = (uint *)precvbuf->pbuf;
			isevt = le32_to_cpu(*(pbuf + 1)) & 0x1ff;
			if ((isevt & 0x1ff) == 0x1ff) {
				r8712_rxcmd_event_hdl(padapter, pbuf);
				precvbuf->reuse = true;
				r8712_read_port(padapter, precvpriv->ff_hwaddr,
						0, (unsigned char *)precvbuf);
			} else {
				_pkt *pskb = precvbuf->pskb;

				skb_put(pskb, purb->actual_length);
				skb_queue_tail(&precvpriv->rx_skb_queue, pskb);
				tasklet_hi_schedule(&precvpriv->recv_tasklet);
				precvbuf->pskb = NULL;
				precvbuf->reuse = false;
				r8712_read_port(padapter, precvpriv->ff_hwaddr,
						0, (unsigned char *)precvbuf);
			}
		}
	} else {
		switch (purb->status) {
		case -EINVAL:
		case -EPIPE:
		case -ENODEV:
		case -ESHUTDOWN:
		case -ENOENT:
			padapter->bDriverStopped = true;
			break;
		case -EPROTO:
			precvbuf->reuse = true;
			r8712_read_port(padapter, precvpriv->ff_hwaddr, 0,
				  (unsigned char *)precvbuf);
			break;
		case -EINPROGRESS:
			netdev_err(padapter->pnetdev, "ERROR: URB IS IN PROGRESS!\n");
			break;
		default:
			break;
		}
	}
}
