rtl8821ae_enable_hw_security_config(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 sec_reg_value;
	u8 tmp;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG,
		 "PairwiseEncAlgorithm = %d GroupEncAlgorithm = %d\n",
		  rtlpriv->sec.pairwise_enc_algorithm,
		  rtlpriv->sec.group_enc_algorithm);

	if (rtlpriv->cfg->mod_params->sw_crypto || rtlpriv->sec.use_sw_sec) {
		RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
			 "not open hw encryption\n");
		return;
	}

	sec_reg_value = SCR_TXENCENABLE | SCR_RXDECENABLE;

	if (rtlpriv->sec.use_defaultkey) {
		sec_reg_value |= SCR_TXUSEDK;
		sec_reg_value |= SCR_RXUSEDK;
	}

	sec_reg_value |= (SCR_RXBCUSEDK | SCR_TXBCUSEDK);

	tmp = rtl_read_byte(rtlpriv, REG_CR + 1);
	rtl_write_byte(rtlpriv, REG_CR + 1, tmp | BIT(1));

	RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
		 "The SECR-value %x\n", sec_reg_value);

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_WPA_CONFIG, &sec_reg_value);
}
