si5351_clkout_get_parent(struct clk_hw *hw)
{
	struct si5351_hw_data *hwdata =
		container_of(hw, struct si5351_hw_data, hw);
	int index = 0;
	unsigned char val;

	val = si5351_reg_read(hwdata->drvdata, SI5351_CLK0_CTRL + hwdata->num);
	switch (val & SI5351_CLK_INPUT_MASK) {
	case SI5351_CLK_INPUT_MULTISYNTH_N:
		index = 0;
		break;
	case SI5351_CLK_INPUT_MULTISYNTH_0_4:
		index = 1;
		break;
	case SI5351_CLK_INPUT_XTAL:
		index = 2;
		break;
	case SI5351_CLK_INPUT_CLKIN:
		index = 3;
		break;
	}

	return index;
}
