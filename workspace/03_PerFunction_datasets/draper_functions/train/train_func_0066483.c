alps_raw_event(struct hid_device *hdev,
		struct hid_report *report, u8 *data, int size)
{
	unsigned int x, y, z;
	int i;
	short sp_x, sp_y;
	struct u1_dev *hdata = hid_get_drvdata(hdev);

	switch (data[0]) {
	case U1_MOUSE_REPORT_ID:
		break;
	case U1_FEATURE_REPORT_ID:
		break;
	case U1_ABSOLUTE_REPORT_ID:
		for (i = 0; i < MAX_TOUCHES; i++) {
			u8 *contact = &data[i * 5];

			x = get_unaligned_le16(contact + 3);
			y = get_unaligned_le16(contact + 5);
			z = contact[7] & 0x7F;

			input_mt_slot(hdata->input, i);

			if (z != 0) {
				input_mt_report_slot_state(hdata->input,
					MT_TOOL_FINGER, 1);
				input_report_abs(hdata->input,
					ABS_MT_POSITION_X, x);
				input_report_abs(hdata->input,
					ABS_MT_POSITION_Y, y);
				input_report_abs(hdata->input,
					ABS_MT_PRESSURE, z);
			} else {
				input_mt_report_slot_state(hdata->input,
					MT_TOOL_FINGER, 0);
			}
		}

		input_mt_sync_frame(hdata->input);

		input_report_key(hdata->input, BTN_LEFT,
			data[1] & 0x1);
		input_report_key(hdata->input, BTN_RIGHT,
			(data[1] & 0x2));
		input_report_key(hdata->input, BTN_MIDDLE,
			(data[1] & 0x4));

		input_sync(hdata->input);

		return 1;

	case U1_SP_ABSOLUTE_REPORT_ID:
		sp_x = get_unaligned_le16(data+2);
		sp_y = get_unaligned_le16(data+4);

		sp_x = sp_x / 8;
		sp_y = sp_y / 8;

		input_report_rel(hdata->input2, REL_X, sp_x);
		input_report_rel(hdata->input2, REL_Y, sp_y);

		input_report_key(hdata->input2, BTN_LEFT,
			data[1] & 0x1);
		input_report_key(hdata->input2, BTN_RIGHT,
			(data[1] & 0x2));
		input_report_key(hdata->input2, BTN_MIDDLE,
			(data[1] & 0x4));

		input_sync(hdata->input2);

		return 1;
	}

	return 0;
}
