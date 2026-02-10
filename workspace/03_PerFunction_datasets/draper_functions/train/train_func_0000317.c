r8712_os_recvbuf_resource_free(struct _adapter *padapter,
			     struct recv_buf *precvbuf)
{
	if (precvbuf->pskb)
		dev_kfree_skb_any(precvbuf->pskb);
	if (precvbuf->purb) {
		usb_kill_urb(precvbuf->purb);
		usb_free_urb(precvbuf->purb);
	}
	return _SUCCESS;
}
