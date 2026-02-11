sd_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	if (depth_mode)
		return gspca_dev_probe(intf, id, &sd_desc_depth,
				       sizeof(struct sd), THIS_MODULE);
	else
		return gspca_dev_probe(intf, id, &sd_desc_video,
				       sizeof(struct sd), THIS_MODULE);
}
