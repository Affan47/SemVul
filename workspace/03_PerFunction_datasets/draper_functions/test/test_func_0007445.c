uwb_rsv_update_all(struct uwb_rc *rc)
{
	struct uwb_rsv *rsv, *t;
	bool ie_updated = false;

	list_for_each_entry_safe(rsv, t, &rc->reservations, rc_node) {
		if (!rsv->ie_valid) {
			uwb_drp_ie_update(rsv);
			ie_updated = true;
		}
	}

	return ie_updated;
}
