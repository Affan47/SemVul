stmpe_keypad_irq(int irq, void *dev)
{
	struct stmpe_keypad *keypad = dev;
	struct input_dev *input = keypad->input;
	const struct stmpe_keypad_variant *variant = keypad->variant;
	u8 fifo[variant->num_data];
	int ret;
	int i;

	ret = stmpe_keypad_read_data(keypad, fifo);
	if (ret < 0)
		return IRQ_NONE;

	for (i = 0; i < variant->num_normal_data; i++) {
		u8 data = fifo[i];
		int row = (data & STMPE_KPC_DATA_ROW) >> 3;
		int col = data & STMPE_KPC_DATA_COL;
		int code = MATRIX_SCAN_CODE(row, col, STMPE_KEYPAD_ROW_SHIFT);
		bool up = data & STMPE_KPC_DATA_UP;

		if ((data & STMPE_KPC_DATA_NOKEY_MASK)
			== STMPE_KPC_DATA_NOKEY_MASK)
			continue;

		input_event(input, EV_MSC, MSC_SCAN, code);
		input_report_key(input, keypad->keymap[code], !up);
		input_sync(input);
	}

	return IRQ_HANDLED;
}
