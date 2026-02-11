pn533_abort_cmd(struct pn533 *dev, gfp_t flags)
{


	if (dev->device_type == PN533_DEVICE_ACR122U)
		return;


	pn533_send_ack(dev, flags);


	usb_kill_urb(dev->in_urb);
}
