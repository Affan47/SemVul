scratch_reset(struct usb_usbvision *usbvision)
{
	PDEBUG(DBG_SCRATCH, "\n");

	usbvision->scratch_read_ptr = 0;
	usbvision->scratch_write_ptr = 0;
	usbvision->scratch_headermarker_read_ptr = 0;
	usbvision->scratch_headermarker_write_ptr = 0;
	usbvision->isocstate = isoc_state_no_frame;
}
