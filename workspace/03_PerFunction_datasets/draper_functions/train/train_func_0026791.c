rk3288_set_rgmii_speed(struct rk_priv_data *bsp_priv, int speed)
{
	struct device *dev = &bsp_priv->pdev->dev;

	if (IS_ERR(bsp_priv->grf)) {
		dev_err(dev, "Missing rockchip,grf property\n");
		return;
	}

	if (speed == 10)
		regmap_write(bsp_priv->grf, RK3288_GRF_SOC_CON1,
			     RK3288_GMAC_CLK_2_5M);
	else if (speed == 100)
		regmap_write(bsp_priv->grf, RK3288_GRF_SOC_CON1,
			     RK3288_GMAC_CLK_25M);
	else if (speed == 1000)
		regmap_write(bsp_priv->grf, RK3288_GRF_SOC_CON1,
			     RK3288_GMAC_CLK_125M);
	else
		dev_err(dev, "unknown speed value for RGMII! speed=%d", speed);
}
