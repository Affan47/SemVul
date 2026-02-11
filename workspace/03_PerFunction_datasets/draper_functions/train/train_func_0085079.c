wtp_touch_event(struct wtp_data *wd,
	struct hidpp_touchpad_raw_xy_finger *touch_report)
{
	int slot;

	if (!touch_report->finger_id || touch_report->contact_type)

		return;

	slot = input_mt_get_slot_by_key(wd->input, touch_report->finger_id);

	input_mt_slot(wd->input, slot);
	input_mt_report_slot_state(wd->input, MT_TOOL_FINGER,
					touch_report->contact_status);
	if (touch_report->contact_status) {
		input_event(wd->input, EV_ABS, ABS_MT_POSITION_X,
				touch_report->x);
		input_event(wd->input, EV_ABS, ABS_MT_POSITION_Y,
				wd->flip_y ? wd->y_size - touch_report->y :
					     touch_report->y);
		input_event(wd->input, EV_ABS, ABS_MT_PRESSURE,
				touch_report->area);
	}
}
