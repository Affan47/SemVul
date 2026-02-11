hackrf_submit_urbs(struct hackrf_dev *dev)
{
	int i, ret;

	for (i = 0; i < dev->urbs_initialized; i++) {
		dev_dbg(dev->dev, "submit urb=%d\n", i);
		ret = usb_submit_urb(dev->urb_list[i], GFP_ATOMIC);
		if (ret) {
			dev_err(dev->dev, "Could not submit URB no. %d - get them all back\n",
					i);
			hackrf_kill_urbs(dev);
			return ret;
		}
		dev->urbs_submitted++;
	}

	return 0;
}
