si514_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_si514 *data = to_clk_si514(hw);
	struct clk_si514_muldiv settings;
	int err;

	err = si514_calc_muldiv(&settings, rate);
	if (err)
		return err;

	si514_enable_output(data, false);

	err = si514_set_muldiv(data, &settings);
	if (err < 0)
		return err;


	err = regmap_write(data->regmap, SI514_REG_CONTROL, SI514_CONTROL_FCAL);
	if (err < 0)
		return err;


	usleep_range(10000, 12000);

	si514_enable_output(data, true);

	return err;
}
