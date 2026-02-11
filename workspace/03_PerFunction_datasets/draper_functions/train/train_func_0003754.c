get_sample_rate_v2(struct snd_usb_audio *chip, int iface,
			      int altsetting, int clock)
{
	struct usb_device *dev = chip->dev;
	__le32 data;
	int err;

	err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC2_CS_CUR,
			      USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_IN,
			      UAC2_CS_CONTROL_SAM_FREQ << 8,
			      snd_usb_ctrl_intf(chip) | (clock << 8),
			      &data, sizeof(data));
	if (err < 0) {
		dev_warn(&dev->dev, "%d:%d: cannot get freq (v2): err %d\n",
			 iface, altsetting, err);
		return 0;
	}

	return le32_to_cpu(data);
}
