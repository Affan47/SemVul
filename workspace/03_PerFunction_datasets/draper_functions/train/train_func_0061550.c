pctv452e_usb_probe(struct usb_interface *intf,
				const struct usb_device_id *id)
{
	if (0 == dvb_usb_device_init(intf, &pctv452e_properties,
					THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &tt_connect_s2_3600_properties,
					THIS_MODULE, NULL, adapter_nr))
		return 0;

	return -ENODEV;
}
