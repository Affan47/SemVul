uwbd_evt_get_drp_avail(struct uwb_event *evt, unsigned long *bmp)
{
	struct device *dev = &evt->rc->uwb_dev.dev;
	struct uwb_rc_evt_drp_avail *drp_evt;
	int result = -EINVAL;


	if (evt->notif.size < sizeof(*drp_evt)) {
		dev_err(dev, "DRP Availability Change: Not enough "
			"data to decode event [%zu bytes, %zu "
			"needed]\n", evt->notif.size, sizeof(*drp_evt));
		goto error;
	}
	drp_evt = container_of(evt->notif.rceb, struct uwb_rc_evt_drp_avail, rceb);
	buffer_to_bmp(bmp, drp_evt->bmp, UWB_NUM_MAS/8);
	result = 0;
error:
	return result;
}
