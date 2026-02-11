cc_usb_sync(struct cc_usb *cc)
{
	if (_cc_usb_sync(cc, 0) < 0) {
		fprintf(stderr, "USB link timeout\n");
		exit(1);
	}
}
