r8712_usb_read_port_cancel(struct _adapter *padapter)
{
	int i;
	struct recv_buf *precvbuf;

	precvbuf = (struct recv_buf *)padapter->recvpriv.precv_buf;
	for (i = 0; i < NR_RECVBUFF; i++) {
		if (precvbuf->purb)
			usb_kill_urb(precvbuf->purb);
		precvbuf++;
	}
}
