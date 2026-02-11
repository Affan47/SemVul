usbhsh_urb_enqueue(struct usb_hcd *hcd,
			      struct urb *urb,
			      gfp_t mem_flags)
{
	struct usbhsh_hpriv *hpriv = usbhsh_hcd_to_hpriv(hcd);
	struct usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	struct device *dev = usbhs_priv_to_dev(priv);
	struct usb_host_endpoint *ep = urb->ep;
	struct usbhsh_device *new_udev = NULL;
	int is_dir_in = usb_pipein(urb->pipe);
	int ret;

	dev_dbg(dev, "%s (%s)\n", __func__, is_dir_in ? "in" : "out");

	if (!usbhsh_is_running(hpriv)) {
		ret = -EIO;
		dev_err(dev, "host is not running\n");
		goto usbhsh_urb_enqueue_error_not_linked;
	}

	ret = usb_hcd_link_urb_to_ep(hcd, urb);
	if (ret) {
		dev_err(dev, "urb link failed\n");
		goto usbhsh_urb_enqueue_error_not_linked;
	}


	if (!usbhsh_device_get(hpriv, urb)) {
		new_udev = usbhsh_device_attach(hpriv, urb);
		if (!new_udev) {
			ret = -EIO;
			dev_err(dev, "device attach failed\n");
			goto usbhsh_urb_enqueue_error_not_linked;
		}
	}


	if (!usbhsh_ep_to_uep(ep)) {
		ret = usbhsh_endpoint_attach(hpriv, urb, mem_flags);
		if (ret < 0) {
			dev_err(dev, "endpoint attach failed\n");
			goto usbhsh_urb_enqueue_error_free_device;
		}
	}


	ret = usbhsh_pipe_attach(hpriv, urb);
	if (ret < 0) {
		dev_err(dev, "pipe attach failed\n");
		goto usbhsh_urb_enqueue_error_free_endpoint;
	}


	if (usb_pipecontrol(urb->pipe))
		ret = usbhsh_dcp_queue_push(hcd, urb, mem_flags);
	else
		ret = usbhsh_queue_push(hcd, urb, mem_flags);

	return ret;

usbhsh_urb_enqueue_error_free_endpoint:
	usbhsh_endpoint_detach(hpriv, ep);
usbhsh_urb_enqueue_error_free_device:
	if (new_udev)
		usbhsh_device_detach(hpriv, new_udev);
usbhsh_urb_enqueue_error_not_linked:

	dev_dbg(dev, "%s error\n", __func__);

	return ret;
}
