uwb_rsv_handle_drp_avail_change(struct uwb_rc *rc)
{
	struct uwb_drp_backoff_win *bow = &rc->bow;
	struct uwb_rsv *rsv;
	struct uwb_mas_bm mas;

	if (bow->can_reserve_extra_mases == false)
		return;

	list_for_each_entry(rsv, &rc->reservations, rc_node) {
		if (rsv->state == UWB_RSV_STATE_O_ESTABLISHED ||
		    rsv->state == UWB_RSV_STATE_O_TO_BE_MOVED) {
			uwb_drp_available(rc, &mas);
			bitmap_or(mas.bm, mas.bm, rsv->mas.bm, UWB_NUM_MAS);
			uwb_rsv_try_move(rsv, &mas);
		}
	}

}
