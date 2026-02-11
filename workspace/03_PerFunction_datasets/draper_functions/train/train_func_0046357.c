ds_recv_data(struct ds_device *dev, unsigned char *buf, int size)
{
	int count, err;


	count = 0;
	err = usb_bulk_msg(dev->udev, usb_rcvbulkpipe(dev->udev, dev->ep[EP_DATA_IN]),
				buf, size, &count, 1000);
	if (err < 0) {
		pr_info("Clearing ep0x%x.\n", dev->ep[EP_DATA_IN]);
		usb_clear_halt(dev->udev, usb_rcvbulkpipe(dev->udev, dev->ep[EP_DATA_IN]));
		ds_recv_status(dev, NULL, true);
		return err;
	}

#if 0
	{
		int i;

		printk("%s: count=%d: ", __func__, count);
		for (i=0; i<count; ++i)
			printk("%02x ", buf[i]);
		printk("\n");
	}
#endif
	return count;
}
