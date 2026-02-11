palmas_clks_is_prepared(struct clk_hw *hw)
{
	struct palmas_clock_info *cinfo = to_palmas_clks_info(hw);
	int ret;
	u32 val;

	if (cinfo->ext_control_pin)
		return 1;

	ret = palmas_read(cinfo->palmas, PALMAS_RESOURCE_BASE,
			  cinfo->clk_desc->control_reg, &val);
	if (ret < 0) {
		dev_err(cinfo->dev, "Reg 0x%02x read failed, %d\n",
			cinfo->clk_desc->control_reg, ret);
		return ret;
	}
	return !!(val & cinfo->clk_desc->enable_mask);
}
