lcd_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct usb_lcd *dev;
	u16 bcdDevice;
	char buf[30];

	dev = file->private_data;
	if (dev == NULL)
		return -ENODEV;

	switch (cmd) {
	case IOCTL_GET_HARD_VERSION:
		mutex_lock(&lcd_mutex);
		bcdDevice = le16_to_cpu((dev->udev)->descriptor.bcdDevice);
		sprintf(buf, "%1d%1d.%1d%1d",
			(bcdDevice & 0xF000)>>12,
			(bcdDevice & 0xF00)>>8,
			(bcdDevice & 0xF0)>>4,
			(bcdDevice & 0xF));
		mutex_unlock(&lcd_mutex);
		if (copy_to_user((void __user *)arg, buf, strlen(buf)) != 0)
			return -EFAULT;
		break;
	case IOCTL_GET_DRV_VERSION:
		sprintf(buf, DRIVER_VERSION);
		if (copy_to_user((void __user *)arg, buf, strlen(buf)) != 0)
			return -EFAULT;
		break;
	default:
		return -ENOTTY;
		break;
	}

	return 0;
}
