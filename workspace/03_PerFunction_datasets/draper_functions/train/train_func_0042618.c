wacom_dtu_irq(struct wacom_wac *wacom)
{
	unsigned char *data = wacom->data;
	struct input_dev *input = wacom->pen_input;
	int prox = data[1] & 0x20;

	dev_dbg(input->dev.parent,
		"%s: received report #%d", __func__, data[0]);

	if (prox) {

		wacom->tool[0] = (data[1] & 0x0c) ? BTN_TOOL_RUBBER : BTN_TOOL_PEN;
		if (wacom->tool[0] == BTN_TOOL_PEN)
			wacom->id[0] = STYLUS_DEVICE_ID;
		else
			wacom->id[0] = ERASER_DEVICE_ID;
	}
	input_report_key(input, BTN_STYLUS, data[1] & 0x02);
	input_report_key(input, BTN_STYLUS2, data[1] & 0x10);
	input_report_abs(input, ABS_X, le16_to_cpup((__le16 *)&data[2]));
	input_report_abs(input, ABS_Y, le16_to_cpup((__le16 *)&data[4]));
	input_report_abs(input, ABS_PRESSURE, ((data[7] & 0x01) << 8) | data[6]);
	input_report_key(input, BTN_TOUCH, data[1] & 0x05);
	if (!prox)
		wacom->id[0] = 0;
	input_report_key(input, wacom->tool[0], prox);
	input_report_abs(input, ABS_MISC, wacom->id[0]);
	return 1;
}
