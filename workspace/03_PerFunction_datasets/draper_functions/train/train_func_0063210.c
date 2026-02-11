sisusb_get_sisusb_lock_and_check(unsigned short console)
{
	struct sisusb_usb_data *sisusb;


	if (in_atomic())
		return NULL;

	sisusb = sisusb_get_sisusb(console);
	if (!sisusb)
		return NULL;

	mutex_lock(&sisusb->lock);

	if (!sisusb_sisusb_valid(sisusb) ||
	    !sisusb->havethisconsole[console]) {
		mutex_unlock(&sisusb->lock);
		return NULL;
	}

	return sisusb;
}
