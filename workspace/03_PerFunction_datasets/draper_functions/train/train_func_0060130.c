max7359_interrupt(int irq, void *dev_id)
{
	struct max7359_keypad *keypad = dev_id;
	struct input_dev *input_dev = keypad->input_dev;
	int val, row, col, release, code;

	val = max7359_read_reg(keypad->client, MAX7359_REG_KEYFIFO);
	row = val & 0x7;
	col = (val >> 3) & 0x7;
	release = val & 0x40;

	code = MATRIX_SCAN_CODE(row, col, MAX7359_ROW_SHIFT);

	dev_dbg(&keypad->client->dev,
		"key[%d:%d] %s\n", row, col, release ? "release" : "press");

	input_event(input_dev, EV_MSC, MSC_SCAN, code);
	input_report_key(input_dev, keypad->keycodes[code], !release);
	input_sync(input_dev);

	return IRQ_HANDLED;
}
