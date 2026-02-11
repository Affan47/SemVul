stih4xx_fix_retime_src(void *priv, u32 spd)
{
	struct sti_dwmac *dwmac = priv;
	u32 src = dwmac->tx_retime_src;
	u32 reg = dwmac->ctrl_reg;
	u32 freq = 0;

	if (dwmac->interface == PHY_INTERFACE_MODE_MII) {
		src = TX_RETIME_SRC_TXCLK;
	} else if (dwmac->interface == PHY_INTERFACE_MODE_RMII) {
		if (dwmac->ext_phyclk) {
			src = TX_RETIME_SRC_PHYCLK;
		} else {
			src = TX_RETIME_SRC_CLKGEN;
			freq = DWMAC_50MHZ;
		}
	} else if (IS_PHY_IF_MODE_RGMII(dwmac->interface)) {

		if (spd == SPEED_1000) {
			freq = DWMAC_125MHZ;
		} else {

			src = TX_RETIME_SRC_CLKGEN;
			if (spd == SPEED_100)
				freq = DWMAC_25MHZ;
			else if (spd == SPEED_10)
				freq = DWMAC_2_5MHZ;
		}
	}

	if (src == TX_RETIME_SRC_CLKGEN && dwmac->clk && freq)
		clk_set_rate(dwmac->clk, freq);

	regmap_update_bits(dwmac->regmap, reg, STIH4XX_RETIME_SRC_MASK,
			   stih4xx_tx_retime_val[src]);
}
