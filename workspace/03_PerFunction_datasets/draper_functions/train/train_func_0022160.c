mv_u3d_stop_activity(struct mv_u3d *u3d, struct usb_gadget_driver *driver)
{
	struct mv_u3d_ep	*ep;

	mv_u3d_nuke(&u3d->eps[1], -ESHUTDOWN);

	list_for_each_entry(ep, &u3d->gadget.ep_list, ep.ep_list) {
		mv_u3d_nuke(ep, -ESHUTDOWN);
	}


	if (driver) {
		spin_unlock(&u3d->lock);
		driver->disconnect(&u3d->gadget);
		spin_lock(&u3d->lock);
	}
}
