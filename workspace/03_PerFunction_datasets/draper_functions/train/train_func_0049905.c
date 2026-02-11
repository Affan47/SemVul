bcm_kp_report_keys(struct bcm_kp *kp, int reg_num, int pull_mode)
{
	unsigned long state, change;
	int bit_nr;
	int key_press;
	int row, col;
	unsigned int keycode;


	writel(0xFFFFFFFF, kp->base + KPICRN_OFFSET(reg_num));

	state = readl(kp->base + KPSSRN_OFFSET(reg_num));
	change = kp->last_state[reg_num] ^ state;
	kp->last_state[reg_num] = state;

	for_each_set_bit(bit_nr, &change, BITS_PER_LONG) {
		key_press = state & BIT(bit_nr);

		key_press = pull_mode ? !key_press : key_press;
		row = BIT_TO_ROW_SSRN(bit_nr, reg_num);
		col = BIT_TO_COL(bit_nr);
		keycode = bcm_kp_get_keycode(kp, row, col);
		input_report_key(kp->input_dev, keycode, key_press);
	}
}
