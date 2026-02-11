usbhsh_endpoint_disable(struct usb_hcd *hcd,
				    struct usb_host_endpoint *ep)
{
	struct usbhsh_ep *uep = usbhsh_ep_to_uep(ep);
	struct usbhsh_device *udev;
	struct usbhsh_hpriv *hpriv;


	if (!uep)
		return;

	udev	= usbhsh_uep_to_udev(uep);
	hpriv	= usbhsh_hcd_to_hpriv(hcd);

	usbhsh_endpoint_detach(hpriv, ep);


	if (!usbhsh_device_has_endpoint(udev))
		usbhsh_device_detach(hpriv, udev);
}
