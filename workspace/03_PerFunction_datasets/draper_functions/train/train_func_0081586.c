device_add(struct usb_device *usbdev)
{
	int res;
	int id = get_next_device_id();
	struct mux_device *dev;
	usbmuxd_log(LL_NOTICE, "Connecting to new device on location 0x%x as ID %d", usb_get_location(usbdev), id);
	dev = malloc(sizeof(struct mux_device));
	dev->id = id;
	dev->usbdev = usbdev;
	dev->state = MUXDEV_INIT;
	dev->next_sport = 1;
	dev->pktbuf = malloc(DEV_PKTBUF_SIZE);
	dev->pktlen = 0;
	struct version_header vh;
	vh.major = htonl(1);
	vh.minor = htonl(0);
	vh.padding = 0;
	if((res = send_packet(dev, MUX_PROTO_VERSION, &vh, NULL, 0)) < 0) {
		usbmuxd_log(LL_ERROR, "Error sending version request packet to device %d\n", id);
		free(dev);
		return res;
	}
	collection_add(&device_list, dev);
	return 0;
}
