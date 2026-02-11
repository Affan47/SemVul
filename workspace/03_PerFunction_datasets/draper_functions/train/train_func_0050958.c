handler_ext(struct wiimote_data *wdata, const __u8 *payload,
			size_t len)
{
	static const __u8 invalid[21] = { 0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff };
	const __u8 *iter, *mods;
	const struct wiimod_ops *ops;
	bool is_mp;

	if (len > 21)
		len = 21;
	if (len < 6 || !memcmp(payload, invalid, len))
		return;


	if (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE) {

		if (payload[5] & 0x01)
			return;

		if (payload[4] & 0x01) {
			if (!(wdata->state.flags & WIIPROTO_FLAG_MP_PLUGGED)) {
				hid_dbg(wdata->hdev, "MP hotplug: 1\n");
				wdata->state.flags |= WIIPROTO_FLAG_MP_PLUGGED;
				__wiimote_schedule(wdata);
			}
		} else {
			if (wdata->state.flags & WIIPROTO_FLAG_MP_PLUGGED) {
				hid_dbg(wdata->hdev, "MP hotplug: 0\n");
				wdata->state.flags &= ~WIIPROTO_FLAG_MP_PLUGGED;
				wdata->state.flags &= ~WIIPROTO_FLAG_EXT_ACTIVE;
				__wiimote_schedule(wdata);
			}
		}


		is_mp = payload[5] & 0x02;
	} else {
		is_mp = false;
	}


	if (!(wdata->state.flags & WIIPROTO_FLAG_EXT_ACTIVE) && !is_mp)
		return;


	ops = wiimod_ext_table[wdata->state.exttype];
	if (is_mp && ops->in_mp) {
		ops->in_mp(wdata, payload);
		return;
	} else if (!is_mp && valid_ext_handler(ops, len)) {
		ops->in_ext(wdata, payload);
		return;
	}


	ops = &wiimod_mp;
	if (is_mp && ops->in_mp) {
		ops->in_mp(wdata, payload);
		return;
	} else if (!is_mp && valid_ext_handler(ops, len)) {
		ops->in_ext(wdata, payload);
		return;
	}


	mods = wiimote_devtype_mods[wdata->state.devtype];
	for (iter = mods; *iter != WIIMOD_NULL; ++iter) {
		ops = wiimod_table[*iter];
		if (is_mp && ops->in_mp) {
			ops->in_mp(wdata, payload);
			return;
		} else if (!is_mp && valid_ext_handler(ops, len)) {
			ops->in_ext(wdata, payload);
			return;
		}
	}
}
