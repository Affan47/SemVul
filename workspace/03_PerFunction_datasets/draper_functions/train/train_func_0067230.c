frontend_changed(struct xenbus_device *dev,
			     enum xenbus_state frontend_state)
{
	struct backend_info *be = dev_get_drvdata(&dev->dev);

	pr_debug("%s -> %s\n", dev->otherend, xenbus_strstate(frontend_state));

	be->frontend_state = frontend_state;

	switch (frontend_state) {
	case XenbusStateInitialising:
		set_backend_state(be, XenbusStateInitWait);
		break;

	case XenbusStateInitialised:
		break;

	case XenbusStateConnected:
		set_backend_state(be, XenbusStateConnected);
		break;

	case XenbusStateClosing:
		set_backend_state(be, XenbusStateClosing);
		break;

	case XenbusStateClosed:
		set_backend_state(be, XenbusStateClosed);
		if (xenbus_dev_is_online(dev))
			break;

	case XenbusStateUnknown:
		set_backend_state(be, XenbusStateClosed);
		device_unregister(&dev->dev);
		break;

	default:
		xenbus_dev_fatal(dev, -EINVAL, "saw state %d at frontend",
				 frontend_state);
		break;
	}
}
