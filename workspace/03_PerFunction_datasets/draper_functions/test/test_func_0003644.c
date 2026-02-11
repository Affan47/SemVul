m920x_probe(struct usb_interface *intf,
		       const struct usb_device_id *id)
{
	struct dvb_usb_device *d = NULL;
	int ret;
	struct m920x_inits *rc_init_seq = NULL;
	int bInterfaceNumber = intf->cur_altsetting->desc.bInterfaceNumber;

	deb("Probing for m920x device at interface %d\n", bInterfaceNumber);

	if (bInterfaceNumber == 0) {


		ret = dvb_usb_device_init(intf, &megasky_properties,
					  THIS_MODULE, &d, adapter_nr);
		if (ret == 0) {
			rc_init_seq = megasky_rc_init;
			goto found;
		}

		ret = dvb_usb_device_init(intf, &digivox_mini_ii_properties,
					  THIS_MODULE, &d, adapter_nr);
		if (ret == 0) {

			goto found;
		}


		ret = dvb_usb_device_init(intf, &tvwalkertwin_properties,
					  THIS_MODULE, &d, adapter_nr);
		if (ret == 0) {
			rc_init_seq = tvwalkertwin_rc_init;
			goto found;
		}

		ret = dvb_usb_device_init(intf, &dposh_properties,
					  THIS_MODULE, &d, adapter_nr);
		if (ret == 0) {

			goto found;
		}

		ret = dvb_usb_device_init(intf, &pinnacle_pctv310e_properties,
					  THIS_MODULE, &d, adapter_nr);
		if (ret == 0) {
			rc_init_seq = pinnacle310e_init;
			goto found;
		}

		ret = dvb_usb_device_init(intf, &vp7049_properties,
					  THIS_MODULE, &d, adapter_nr);
		if (ret == 0) {
			rc_init_seq = vp7049_rc_init;
			goto found;
		}

		return ret;
	} else {


	}

 found:
	if ((ret = m920x_init_ep(intf)) < 0)
		return ret;

	if (d && (ret = m920x_init(d, rc_init_seq)) != 0)
		return ret;

	return ret;
}
