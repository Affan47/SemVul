get_urb_to_r8a66597_addr(struct r8a66597 *r8a66597, struct urb *urb)
{
	struct r8a66597_device *dev = get_urb_to_r8a66597_dev(r8a66597, urb);

	return (usb_pipedevice(urb->pipe) == 0) ? 0 : dev->address;
}
