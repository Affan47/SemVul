apple_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{
	struct apple_sc *asc = hid_get_drvdata(hdev);

	if (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput ||
			!usage->type)
		return 0;

	if ((asc->quirks & APPLE_INVERT_HWHEEL) &&
			usage->code == REL_HWHEEL) {
		input_event(field->hidinput->input, usage->type, usage->code,
				-value);
		return 1;
	}

	if ((asc->quirks & APPLE_HAS_FN) &&
			hidinput_apple_event(hdev, field->hidinput->input,
				usage, value))
		return 1;


	return 0;
}
