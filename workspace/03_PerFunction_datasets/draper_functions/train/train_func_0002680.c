destroy_urbs(struct gspca_dev *gspca_dev)
{
	struct urb *urb;
	unsigned int i;

	PDEBUG(D_STREAM, "kill transfer");
	for (i = 0; i < MAX_NURBS; i++) {
		urb = gspca_dev->urb[i];
		if (urb == NULL)
			break;

		gspca_dev->urb[i] = NULL;
		usb_kill_urb(urb);
		usb_free_coherent(gspca_dev->dev,
				  urb->transfer_buffer_length,
				  urb->transfer_buffer,
				  urb->transfer_dma);
		usb_free_urb(urb);
	}
}
