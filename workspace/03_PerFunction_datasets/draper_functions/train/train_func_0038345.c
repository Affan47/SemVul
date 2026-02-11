u132_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct u132 *u132 = hcd_to_u132(hcd);
	if (u132->going > 2) {
		dev_err(&u132->platform_dev->dev, "device has been removed %d\n"
			, u132->going);
		return -ENODEV;
	} else {
		u8 usb_addr = usb_pipedevice(urb->pipe);
		u8 usb_endp = usb_pipeendpoint(urb->pipe);
		u8 address = u132->addr[usb_addr].address;
		struct u132_udev *udev = &u132->udev[address];
		if (usb_pipein(urb->pipe)) {
			u8 endp_number = udev->endp_number_in[usb_endp];
			struct u132_endp *endp = u132->endp[endp_number - 1];
			return u132_endp_urb_dequeue(u132, endp, urb, status);
		} else {
			u8 endp_number = udev->endp_number_out[usb_endp];
			struct u132_endp *endp = u132->endp[endp_number - 1];
			return u132_endp_urb_dequeue(u132, endp, urb, status);
		}
	}
}
