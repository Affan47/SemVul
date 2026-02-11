uwbd_evt_handle_rc_beacon(struct uwb_event *evt)
{
	int result = -EINVAL;
	struct uwb_rc *rc;
	struct uwb_rc_evt_beacon *be;
	struct uwb_beacon_frame *bf;
	struct uwb_beca_e *bce;

	rc = evt->rc;
	be = container_of(evt->notif.rceb, struct uwb_rc_evt_beacon, rceb);
	result = uwb_verify_beacon(rc, evt, be);
	if (result < 0)
		return result;


	if (be->bBeaconType == UWB_RC_BEACON_TYPE_OL_ALIEN ||
	    be->bBeaconType == UWB_RC_BEACON_TYPE_NOL_ALIEN) {
		return -ENOSYS;
	}

	bf = (struct uwb_beacon_frame *) be->BeaconInfo;


	if (uwb_mac_addr_bcast(&bf->Device_Identifier))
		return 0;

	mutex_lock(&rc->uwb_beca.mutex);
	bce = __uwb_beca_find_bymac(rc, &bf->Device_Identifier);
	if (bce == NULL) {

		uwb_beacon_print(evt->rc, be, bf);
		bce = __uwb_beca_add(rc, be, bf, evt->ts_jiffies);
		if (bce == NULL) {
			mutex_unlock(&rc->uwb_beca.mutex);
			return -ENOMEM;
		}
	}
	mutex_unlock(&rc->uwb_beca.mutex);

	mutex_lock(&bce->mutex);

	kfree(bce->be);


	bce->ts_jiffies = evt->ts_jiffies;
	bce->be = be;
	bce->dev_addr = bf->hdr.SrcAddr;
	bce->mac_addr = &bf->Device_Identifier;
	be->wBPSTOffset = le16_to_cpu(be->wBPSTOffset);
	be->wBeaconInfoLength = le16_to_cpu(be->wBeaconInfoLength);
	stats_add_sample(&bce->lqe_stats, be->bLQI - 7);
	stats_add_sample(&bce->rssi_stats, be->bRSSI + 18);


	if (bce->uwb_dev == NULL)
		uwbd_dev_onair(evt->rc, bce);

	mutex_unlock(&bce->mutex);

	return 1;
}
