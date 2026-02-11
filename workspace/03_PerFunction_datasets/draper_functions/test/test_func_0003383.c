ftdi_elan_write(struct file *file,
			       const char __user *user_buffer, size_t count,
			       loff_t *ppos)
{
	int retval = 0;
	struct urb *urb;
	char *buf;
	struct usb_ftdi *ftdi = file->private_data;

	if (ftdi->disconnected > 0) {
		return -ENODEV;
	}
	if (count == 0) {
		goto exit;
	}
	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb) {
		retval = -ENOMEM;
		goto error_1;
	}
	buf = usb_alloc_coherent(ftdi->udev, count, GFP_KERNEL,
				 &urb->transfer_dma);
	if (!buf) {
		retval = -ENOMEM;
		goto error_2;
	}
	if (copy_from_user(buf, user_buffer, count)) {
		retval = -EFAULT;
		goto error_3;
	}
	usb_fill_bulk_urb(urb, ftdi->udev, usb_sndbulkpipe(ftdi->udev,
							   ftdi->bulk_out_endpointAddr), buf, count,
			  ftdi_elan_write_bulk_callback, ftdi);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	retval = usb_submit_urb(urb, GFP_KERNEL);
	if (retval) {
		dev_err(&ftdi->udev->dev,
			"failed submitting write urb, error %d\n", retval);
		goto error_3;
	}
	usb_free_urb(urb);

exit:
	return count;
error_3:
	usb_free_coherent(ftdi->udev, count, buf, urb->transfer_dma);
error_2:
	usb_free_urb(urb);
error_1:
	return retval;
}
