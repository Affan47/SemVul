cavan_usb_init(const char *dev_path, struct cavan_usb_descriptor *desc)
{
	int i, j;
	int fd;
	int ret;

	fd = open(dev_path, O_RDWR);
	if (fd < 0)
	{
		error_msg("open device \"%s\" failed", dev_path);
		return fd;
	}

	ret = fusb_read_cavan_descriptor(fd, desc);
	if (ret < 0)
	{
		pr_red_info("fusb_read_cavan_descriptor");
		goto out_close_fd;
	}

#if CAVAN_USB_DEBUG
	show_cavan_usb_descriptor(desc);
#endif

	for (i = desc->if_count - 1; i >= 0; i--)
	{
		if (usb_clam_interface(fd, desc->if_descs[i].if_desc.bInterfaceNumber, desc->dev_desc.iSerialNumber, desc->serial) < 0)
		{
			continue;
		}

		desc->epin_curr = -1;
		desc->epout_curr = -1;

		for (j = desc->if_descs[i].if_desc.bNumEndpoints - 1; j >= 0; j--)
		{
			if (desc->if_descs[i].ep_descs[j].bEndpointAddress & USB_ENDPOINT_DIR_MASK)
			{
				desc->epin_curr = desc->if_descs[i].ep_descs[j].bEndpointAddress;
			}
			else
			{
				desc->epout_curr = desc->if_descs[i].ep_descs[j].bEndpointAddress;
			}
		}

		if (desc->epin_curr > 0 && desc->epout_curr > 0)
		{
			break;
		}
	}

	if (i < 0)
	{
		return -ENOENT;
	}

	memset(&desc->urb_read, 0, sizeof(desc->urb_read));
	memset(&desc->urb_write, 0, sizeof(desc->urb_write));
	desc->urb_read.type = desc->urb_write.type = USBDEVFS_URB_TYPE_BULK;
	desc->urb_read.endpoint = desc->epin_curr;
	desc->urb_write.endpoint = desc->epout_curr;

	desc->fd = fd;
	text_copy(desc->dev_path, dev_path);
	pthread_mutex_init(&desc->lock, 0);
	pthread_cond_init(&desc->notify_read, 0);
	pthread_cond_init(&desc->notify_write, 0);

	ret = pthread_create(&desc->thread_notify, NULL, cavan_usb_notify_handle, desc);
	if (ret < 0)
	{
		print_error("pthread_create");
		goto out_close_fd;
	}

	return 0;

out_close_fd:
	close(fd);

	return ret;
}
