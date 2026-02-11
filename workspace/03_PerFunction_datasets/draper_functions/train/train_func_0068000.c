usbhs_mod_host_probe(struct usbhs_priv *priv)
{
	struct usbhsh_hpriv *hpriv;
	struct usb_hcd *hcd;
	struct usbhsh_device *udev;
	struct device *dev = usbhs_priv_to_dev(priv);
	int i;


	hcd = usb_create_hcd(&usbhsh_driver, dev, usbhsh_hcd_name);
	if (!hcd) {
		dev_err(dev, "Failed to create hcd\n");
		return -ENOMEM;
	}
	hcd->has_tt = 1;


	hpriv = usbhsh_hcd_to_hpriv(hcd);


	usbhs_mod_register(priv, &hpriv->mod, USBHS_HOST);


	hpriv->mod.name		= "host";
	hpriv->mod.start	= usbhsh_start;
	hpriv->mod.stop		= usbhsh_stop;
	usbhsh_port_stat_init(hpriv);


	usbhsh_for_each_udev_with_dev0(udev, hpriv, i) {
		udev->usbv	= NULL;
		INIT_LIST_HEAD(&udev->ep_list_head);
	}

	dev_info(dev, "host probed\n");

	return 0;
}
