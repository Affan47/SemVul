uwb_rsv_stroke_timer(struct uwb_rsv *rsv)
{
	int sframes = UWB_MAX_LOST_BEACONS;


	if (rsv->state == UWB_RSV_STATE_NONE) {
		sframes = 0;
	} else if (rsv->is_multicast) {
		if (rsv->state == UWB_RSV_STATE_O_INITIATED
		    || rsv->state == UWB_RSV_STATE_O_MOVE_EXPANDING
		    || rsv->state == UWB_RSV_STATE_O_MOVE_COMBINING
		    || rsv->state == UWB_RSV_STATE_O_MOVE_REDUCING)
			sframes = 1;
		if (rsv->state == UWB_RSV_STATE_O_ESTABLISHED)
			sframes = 0;

	}

	if (sframes > 0) {


		unsigned timeout_us = (sframes + 2) * UWB_SUPERFRAME_LENGTH_US;
		mod_timer(&rsv->timer, jiffies + usecs_to_jiffies(timeout_us));
	} else
		del_timer(&rsv->timer);
}
