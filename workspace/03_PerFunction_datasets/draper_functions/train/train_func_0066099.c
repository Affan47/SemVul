ar9003_hw_antdiv_comb_conf_get(struct ath_hw *ah,
					   struct ath_hw_antcomb_conf *antconf)
{
	u32 regval;

	regval = REG_READ(ah, AR_PHY_MC_GAIN_CTRL);
	antconf->main_lna_conf = (regval & AR_PHY_ANT_DIV_MAIN_LNACONF) >>
				  AR_PHY_ANT_DIV_MAIN_LNACONF_S;
	antconf->alt_lna_conf = (regval & AR_PHY_ANT_DIV_ALT_LNACONF) >>
				 AR_PHY_ANT_DIV_ALT_LNACONF_S;
	antconf->fast_div_bias = (regval & AR_PHY_ANT_FAST_DIV_BIAS) >>
				  AR_PHY_ANT_FAST_DIV_BIAS_S;

	if (AR_SREV_9330_11(ah)) {
		antconf->lna1_lna2_switch_delta = -1;
		antconf->lna1_lna2_delta = -9;
		antconf->div_group = 1;
	} else if (AR_SREV_9485(ah)) {
		antconf->lna1_lna2_switch_delta = -1;
		antconf->lna1_lna2_delta = -9;
		antconf->div_group = 2;
	} else if (AR_SREV_9565(ah)) {
		antconf->lna1_lna2_switch_delta = 3;
		antconf->lna1_lna2_delta = -9;
		antconf->div_group = 3;
	} else {
		antconf->lna1_lna2_switch_delta = -1;
		antconf->lna1_lna2_delta = -3;
		antconf->div_group = 0;
	}
}
