ntrig_input_configured(struct hid_device *hid,
		struct hid_input *hidinput)

{
	struct input_dev *input = hidinput->input;

	if (hidinput->report->maxfield < 1)
		return 0;

	switch (hidinput->report->field[0]->application) {
	case HID_DG_PEN:
		input->name = "N-Trig Pen";
		break;
	case HID_DG_TOUCHSCREEN:


		__clear_bit(BTN_TOOL_PEN, input->keybit);
		__clear_bit(BTN_TOOL_FINGER, input->keybit);
		__clear_bit(BTN_0, input->keybit);
		__set_bit(BTN_TOOL_DOUBLETAP, input->keybit);


		input->name = (hidinput->report->field[0]->physical) ?
							"N-Trig Touchscreen" :
							"N-Trig MultiTouch";
		break;
	}

	return 0;
}
