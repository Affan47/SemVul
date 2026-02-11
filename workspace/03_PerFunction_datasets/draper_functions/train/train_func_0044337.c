kszphy_probe(struct phy_device *phydev)
{
	const struct kszphy_type *type = phydev->drv->driver_data;
	const struct device_node *np = phydev->dev.of_node;
	struct kszphy_priv *priv;
	struct clk *clk;
	int ret;

	priv = devm_kzalloc(&phydev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	phydev->priv = priv;

	priv->type = type;

	if (type->led_mode_reg) {
		ret = of_property_read_u32(np, "micrel,led-mode",
				&priv->led_mode);
		if (ret)
			priv->led_mode = -1;

		if (priv->led_mode > 3) {
			dev_err(&phydev->dev, "invalid led mode: 0x%02x\n",
					priv->led_mode);
			priv->led_mode = -1;
		}
	} else {
		priv->led_mode = -1;
	}

	clk = devm_clk_get(&phydev->dev, "rmii-ref");

	if (!IS_ERR_OR_NULL(clk)) {
		unsigned long rate = clk_get_rate(clk);
		bool rmii_ref_clk_sel_25_mhz;

		priv->rmii_ref_clk_sel = type->has_rmii_ref_clk_sel;
		rmii_ref_clk_sel_25_mhz = of_property_read_bool(np,
				"micrel,rmii-reference-clock-select-25-mhz");

		if (rate > 24500000 && rate < 25500000) {
			priv->rmii_ref_clk_sel_val = rmii_ref_clk_sel_25_mhz;
		} else if (rate > 49500000 && rate < 50500000) {
			priv->rmii_ref_clk_sel_val = !rmii_ref_clk_sel_25_mhz;
		} else {
			dev_err(&phydev->dev, "Clock rate out of range: %ld\n", rate);
			return -EINVAL;
		}
	}


	if (phydev->dev_flags & MICREL_PHY_50MHZ_CLK) {
		priv->rmii_ref_clk_sel = true;
		priv->rmii_ref_clk_sel_val = true;
	}

	return 0;
}
