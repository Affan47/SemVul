scsifront_backend_changed(struct xenbus_device *dev,
				      enum xenbus_state backend_state)
{
	struct vscsifrnt_info *info = dev_get_drvdata(&dev->dev);

	pr_debug("%s: %p %u %u\n", __func__, dev, dev->state, backend_state);

	switch (backend_state) {
	case XenbusStateUnknown:
	case XenbusStateInitialising:
	case XenbusStateInitWait:
	case XenbusStateInitialised:
		break;

	case XenbusStateConnected:
		scsifront_read_backend_params(dev, info);

		if (info->pause) {
			scsifront_do_lun_hotplug(info, VSCSIFRONT_OP_READD_LUN);
			xenbus_switch_state(dev, XenbusStateConnected);
			info->pause = 0;
			return;
		}

		if (xenbus_read_driver_state(dev->nodename) ==
		    XenbusStateInitialised)
			scsifront_do_lun_hotplug(info, VSCSIFRONT_OP_ADD_LUN);

		if (dev->state != XenbusStateConnected)
			xenbus_switch_state(dev, XenbusStateConnected);
		break;

	case XenbusStateClosed:
		if (dev->state == XenbusStateClosed)
			break;

	case XenbusStateClosing:
		scsifront_disconnect(info);
		break;

	case XenbusStateReconfiguring:
		scsifront_do_lun_hotplug(info, VSCSIFRONT_OP_DEL_LUN);
		xenbus_switch_state(dev, XenbusStateReconfiguring);
		break;

	case XenbusStateReconfigured:
		scsifront_do_lun_hotplug(info, VSCSIFRONT_OP_ADD_LUN);
		xenbus_switch_state(dev, XenbusStateConnected);
		break;
	}
}
