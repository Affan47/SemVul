as102_release(struct inode *inode, struct file *file)
{
	struct as102_dev_t *dev = NULL;

	dev = file->private_data;
	if (dev != NULL) {

		kref_put(&dev->kref, as102_usb_release);
	}

	return 0;
}
