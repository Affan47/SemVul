keyspan_fake_startup(struct usb_serial *serial)
{
	char	*fw_name;

	dev_dbg(&serial->dev->dev, "Keyspan startup version %04x product %04x\n",
		le16_to_cpu(serial->dev->descriptor.bcdDevice),
		le16_to_cpu(serial->dev->descriptor.idProduct));

	if ((le16_to_cpu(serial->dev->descriptor.bcdDevice) & 0x8000)
								!= 0x8000) {
		dev_dbg(&serial->dev->dev, "Firmware already loaded.  Quitting.\n");
		return 1;
	}


	switch (le16_to_cpu(serial->dev->descriptor.idProduct)) {
	case keyspan_usa28_pre_product_id:
		fw_name = "keyspan/usa28.fw";
		break;

	case keyspan_usa28x_pre_product_id:
		fw_name = "keyspan/usa28x.fw";
		break;

	case keyspan_usa28xa_pre_product_id:
		fw_name = "keyspan/usa28xa.fw";
		break;

	case keyspan_usa28xb_pre_product_id:
		fw_name = "keyspan/usa28xb.fw";
		break;

	case keyspan_usa19_pre_product_id:
		fw_name = "keyspan/usa19.fw";
		break;

	case keyspan_usa19qi_pre_product_id:
		fw_name = "keyspan/usa19qi.fw";
		break;

	case keyspan_mpr_pre_product_id:
		fw_name = "keyspan/mpr.fw";
		break;

	case keyspan_usa19qw_pre_product_id:
		fw_name = "keyspan/usa19qw.fw";
		break;

	case keyspan_usa18x_pre_product_id:
		fw_name = "keyspan/usa18x.fw";
		break;

	case keyspan_usa19w_pre_product_id:
		fw_name = "keyspan/usa19w.fw";
		break;

	case keyspan_usa49w_pre_product_id:
		fw_name = "keyspan/usa49w.fw";
		break;

	case keyspan_usa49wlc_pre_product_id:
		fw_name = "keyspan/usa49wlc.fw";
		break;

	default:
		dev_err(&serial->dev->dev, "Unknown product ID (%04x)\n",
			le16_to_cpu(serial->dev->descriptor.idProduct));
		return 1;
	}

	dev_dbg(&serial->dev->dev, "Uploading Keyspan %s firmware.\n", fw_name);

	if (ezusb_fx1_ihex_firmware_download(serial->dev, fw_name) < 0) {
		dev_err(&serial->dev->dev, "failed to load firmware \"%s\"\n",
			fw_name);
		return -ENOENT;
	}


	return 1;
}
