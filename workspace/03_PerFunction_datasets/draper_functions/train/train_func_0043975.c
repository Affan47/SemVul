hidpp_is_connected(struct hidpp_device *hidpp)
{
	int ret;

	ret = hidpp_root_get_protocol_version(hidpp);
	if (!ret)
		hid_dbg(hidpp->hid_dev, "HID++ %u.%u device connected.\n",
			hidpp->protocol_major, hidpp->protocol_minor);
	return ret == 0;
}
