r8712_xmit_resource_free(struct _adapter *padapter,
			      struct xmit_buf *pxmitbuf)
{
	int i;

	for (i = 0; i < 8; i++) {
		if (pxmitbuf->pxmit_urb[i]) {
			usb_kill_urb(pxmitbuf->pxmit_urb[i]);
			usb_free_urb(pxmitbuf->pxmit_urb[i]);
		}
	}
}
