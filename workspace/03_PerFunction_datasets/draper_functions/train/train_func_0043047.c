device_remove(struct usb_device *usbdev)
{
	FOREACH(struct mux_device *dev, &device_list) {
		if(dev->usbdev == usbdev) {
			usbmuxd_log(LL_NOTICE, "Removed device %d on location 0x%x", dev->id, usb_get_location(usbdev));
			if(dev->state == MUXDEV_ACTIVE) {
				dev->state = MUXDEV_DEAD;
				FOREACH(struct mux_connection *conn, &dev->connections) {
					connection_teardown(conn);
				} ENDFOREACH
				client_device_remove(dev->id);
				collection_free(&dev->connections);
			}
			collection_remove(&device_list, dev);
			free(dev->pktbuf);
			free(dev);
			return;
		}
	} ENDFOREACH
	usbmuxd_log(LL_WARNING, "Cannot find device entry while removing USB device %p on location 0x%x", usbdev, usb_get_location(usbdev));
}
