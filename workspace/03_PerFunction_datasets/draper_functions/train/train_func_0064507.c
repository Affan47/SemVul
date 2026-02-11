wacom_24hdt_irq(struct wacom_wac *wacom)
{
	struct input_dev *input = wacom->touch_input;
	unsigned char *data = wacom->data;
	int i;
	int current_num_contacts = data[61];
	int contacts_to_send = 0;
	int num_contacts_left = 4;
	int byte_per_packet = WACOM_BYTES_PER_24HDT_PACKET;
	int y_offset = 2;

	if (wacom->features.type == WACOM_27QHDT) {
		current_num_contacts = data[63];
		num_contacts_left = 10;
		byte_per_packet = WACOM_BYTES_PER_QHDTHID_PACKET;
		y_offset = 0;
	}


	if (current_num_contacts)
		wacom->num_contacts_left = current_num_contacts;

	contacts_to_send = min(num_contacts_left, wacom->num_contacts_left);

	for (i = 0; i < contacts_to_send; i++) {
		int offset = (byte_per_packet * i) + 1;
		bool touch = (data[offset] & 0x1) && !wacom->shared->stylus_in_proximity;
		int slot = input_mt_get_slot_by_key(input, data[offset + 1]);

		if (slot < 0)
			continue;
		input_mt_slot(input, slot);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, touch);

		if (touch) {
			int t_x = get_unaligned_le16(&data[offset + 2]);
			int t_y = get_unaligned_le16(&data[offset + 4 + y_offset]);

			input_report_abs(input, ABS_MT_POSITION_X, t_x);
			input_report_abs(input, ABS_MT_POSITION_Y, t_y);

			if (wacom->features.type != WACOM_27QHDT) {
				int c_x = get_unaligned_le16(&data[offset + 4]);
				int c_y = get_unaligned_le16(&data[offset + 8]);
				int w = get_unaligned_le16(&data[offset + 10]);
				int h = get_unaligned_le16(&data[offset + 12]);

				input_report_abs(input, ABS_MT_TOUCH_MAJOR, min(w,h));
				input_report_abs(input, ABS_MT_WIDTH_MAJOR,
						 min(w, h) + int_dist(t_x, t_y, c_x, c_y));
				input_report_abs(input, ABS_MT_WIDTH_MINOR, min(w, h));
				input_report_abs(input, ABS_MT_ORIENTATION, w > h);
			}
		}
	}
	input_mt_sync_frame(input);

	wacom->num_contacts_left -= contacts_to_send;
	if (wacom->num_contacts_left <= 0) {
		wacom->num_contacts_left = 0;
		wacom->shared->touch_down = wacom_wac_finger_count_touches(wacom);
	}
	return 1;
}
