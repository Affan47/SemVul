ati_remote_open(struct ati_remote *ati_remote)
{
	int err = 0;

	mutex_lock(&ati_remote->open_mutex);

	if (ati_remote->users++ != 0)
		goto out;


	ati_remote->irq_urb->dev = ati_remote->udev;
	if (usb_submit_urb(ati_remote->irq_urb, GFP_KERNEL)) {
		dev_err(&ati_remote->interface->dev,
			"%s: usb_submit_urb failed!\n", __func__);
		err = -EIO;
	}

out:	mutex_unlock(&ati_remote->open_mutex);
	return err;
}
