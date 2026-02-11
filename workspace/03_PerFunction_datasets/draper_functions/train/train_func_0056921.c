usblp_release(struct inode *inode, struct file *file)
{
	struct usblp *usblp = file->private_data;

	usblp->flags &= ~LP_ABORT;

	mutex_lock(&usblp_mutex);
	usblp->used = 0;
	if (usblp->present) {
		usblp_unlink_urbs(usblp);
		usb_autopm_put_interface(usblp->intf);
	} else
		usblp_cleanup(usblp);
	mutex_unlock(&usblp_mutex);
	return 0;
}
