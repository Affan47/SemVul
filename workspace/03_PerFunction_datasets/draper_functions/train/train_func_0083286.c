net1080_reset(struct usbnet *dev)
{
	u16		usbctl, status, ttl;
	u16		vp;
	int		retval;


	if ((retval = nc_register_read(dev, REG_STATUS, &vp)) < 0) {
		netdev_dbg(dev->net, "can't read %s-%s status: %d\n",
			   dev->udev->bus->bus_name, dev->udev->devpath, retval);
		goto done;
	}
	status = vp;
	nc_dump_status(dev, status);

	if ((retval = nc_register_read(dev, REG_USBCTL, &vp)) < 0) {
		netdev_dbg(dev->net, "can't read USBCTL, %d\n", retval);
		goto done;
	}
	usbctl = vp;
	nc_dump_usbctl(dev, usbctl);

	nc_register_write(dev, REG_USBCTL,
			USBCTL_FLUSH_THIS | USBCTL_FLUSH_OTHER);

	if ((retval = nc_register_read(dev, REG_TTL, &vp)) < 0) {
		netdev_dbg(dev->net, "can't read TTL, %d\n", retval);
		goto done;
	}
	ttl = vp;


	nc_register_write(dev, REG_TTL,
			MK_TTL(NC_READ_TTL_MS, TTL_OTHER(ttl)) );
	netdev_dbg(dev->net, "assigned TTL, %d ms\n", NC_READ_TTL_MS);

	netif_info(dev, link, dev->net, "port %c, peer %sconnected\n",
		   (status & STATUS_PORT_A) ? 'A' : 'B',
		   (status & STATUS_CONN_OTHER) ? "" : "dis");
	retval = 0;

done:
	return retval;
}
