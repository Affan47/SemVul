twidjoy_process_packet(struct twidjoy *twidjoy)
{
	struct input_dev *dev = twidjoy->dev;
	unsigned char *data = twidjoy->data;
	struct twidjoy_button_spec *bp;
	int button_bits, abs_x, abs_y;

	button_bits = ((data[1] & 0x7f) << 7) | (data[0] & 0x7f);

	for (bp = twidjoy_buttons; bp->bitmask; bp++) {
		int value = (button_bits & (bp->bitmask << bp->bitshift)) >> bp->bitshift;
		int i;

		for (i = 0; i < bp->bitmask; i++)
			input_report_key(dev, bp->buttons[i], i+1 == value);
	}

	abs_x = ((data[4] & 0x07) << 5) | ((data[3] & 0x7C) >> 2);
	if (data[4] & 0x08) abs_x -= 256;

	abs_y = ((data[3] & 0x01) << 7) | ((data[2] & 0x7F) >> 0);
	if (data[3] & 0x02) abs_y -= 256;

	input_report_abs(dev, ABS_X, -abs_x);
	input_report_abs(dev, ABS_Y, +abs_y);

	input_sync(dev);
}
