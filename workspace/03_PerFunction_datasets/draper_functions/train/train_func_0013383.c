st5481_release_isocpipes(struct urb *urb[2])
{
	int j;

	for (j = 0; j < 2; j++) {
		usb_kill_urb(urb[j]);
		kfree(urb[j]->transfer_buffer);
		usb_free_urb(urb[j]);
		urb[j] = NULL;
	}
}
