xenbus_alloc_evtchn(struct xenbus_device *dev, int *port)
{
	struct evtchn_alloc_unbound alloc_unbound;
	int err;

	alloc_unbound.dom = DOMID_SELF;
	alloc_unbound.remote_dom = dev->otherend_id;

	err = HYPERVISOR_event_channel_op(EVTCHNOP_alloc_unbound,
					  &alloc_unbound);
	if (err)
		xenbus_dev_fatal(dev, err, "allocating event channel");
	else
		*port = alloc_unbound.port;

	return err;
}
