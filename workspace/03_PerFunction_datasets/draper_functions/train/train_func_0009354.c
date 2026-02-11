m560_raw_event(struct hid_device *hdev, u8 *data, int size)
{
	struct hidpp_device *hidpp = hid_get_drvdata(hdev);
	struct m560_private_data *mydata = hidpp->private_data;


	if (!mydata || !mydata->input) {
		hid_err(hdev, "error in parameter\n");
		return -EINVAL;
	}

	if (size < 7) {
		hid_err(hdev, "error in report\n");
		return 0;
	}

	if (data[0] == REPORT_ID_HIDPP_LONG &&
	    data[2] == M560_SUB_ID && data[6] == 0x00) {


		switch (data[5]) {
		case 0xaf:
			input_report_key(mydata->input, BTN_MIDDLE, 1);
			break;
		case 0xb0:
			input_report_key(mydata->input, BTN_FORWARD, 1);
			break;
		case 0xae:
			input_report_key(mydata->input, BTN_BACK, 1);
			break;
		case 0x00:
			input_report_key(mydata->input, BTN_BACK, 0);
			input_report_key(mydata->input, BTN_FORWARD, 0);
			input_report_key(mydata->input, BTN_MIDDLE, 0);
			break;
		default:
			hid_err(hdev, "error in report\n");
			return 0;
		}
		input_sync(mydata->input);

	} else if (data[0] == 0x02) {


		int v;

		input_report_key(mydata->input, BTN_LEFT,
			!!(data[1] & M560_MOUSE_BTN_LEFT));
		input_report_key(mydata->input, BTN_RIGHT,
			!!(data[1] & M560_MOUSE_BTN_RIGHT));

		if (data[1] & M560_MOUSE_BTN_WHEEL_LEFT)
			input_report_rel(mydata->input, REL_HWHEEL, -1);
		else if (data[1] & M560_MOUSE_BTN_WHEEL_RIGHT)
			input_report_rel(mydata->input, REL_HWHEEL, 1);

		v = hid_snto32(hid_field_extract(hdev, data+3, 0, 12), 12);
		input_report_rel(mydata->input, REL_X, v);

		v = hid_snto32(hid_field_extract(hdev, data+3, 12, 12), 12);
		input_report_rel(mydata->input, REL_Y, v);

		v = hid_snto32(data[6], 8);
		input_report_rel(mydata->input, REL_WHEEL, v);

		input_sync(mydata->input);
	}

	return 1;
}
