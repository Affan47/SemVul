sw_set_global_ctrl(struct ksz_hw *hw)
{
	u16 data;


	data = readw(hw->io + KS8842_SWITCH_CTRL_3_OFFSET);
	data |= SWITCH_FLOW_CTRL;
	writew(data, hw->io + KS8842_SWITCH_CTRL_3_OFFSET);

	data = readw(hw->io + KS8842_SWITCH_CTRL_1_OFFSET);


	data |= SWITCH_AGGR_BACKOFF;


	data |= SWITCH_AGING_ENABLE;
	data |= SWITCH_LINK_AUTO_AGING;

	if (hw->overrides & FAST_AGING)
		data |= SWITCH_FAST_AGING;
	else
		data &= ~SWITCH_FAST_AGING;
	writew(data, hw->io + KS8842_SWITCH_CTRL_1_OFFSET);

	data = readw(hw->io + KS8842_SWITCH_CTRL_2_OFFSET);


	data |= NO_EXC_COLLISION_DROP;
	writew(data, hw->io + KS8842_SWITCH_CTRL_2_OFFSET);
}
