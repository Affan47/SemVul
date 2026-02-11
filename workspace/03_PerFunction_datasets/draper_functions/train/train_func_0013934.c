ezusb_cpucs (
    usb_dev_handle	*device,
    unsigned short	addr,
    int			doRun
) {
    int			status;
    unsigned char	data = doRun ? 0 : 1;

    if (verbose)
	printf("%s\n", data ? "stop CPU" : "reset CPU");
    status = ctrl_msg (device,
	USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	RW_INTERNAL,
	addr, 0,
	&data, 1);
    if (status != 1) {
	char *mesg = "can't modify CPUCS";
	if (status < 0)
	    printf("%s: %s\n", mesg, strerror(errno));
	else
	    printf("%s\n", mesg);
	return 0;
    } else
	return 1;
}
