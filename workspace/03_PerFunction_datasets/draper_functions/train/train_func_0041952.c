rtl8812ae_sw_led_off(struct ieee80211_hw *hw, struct rtl_led *pled)
{
	u16 ledreg = REG_LEDCFG1;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci_priv *pcipriv = rtl_pcipriv(hw);

	switch (pled->ledpin) {
	case LED_PIN_LED0:
		ledreg = REG_LEDCFG1;
		break;

	case LED_PIN_LED1:
		ledreg = REG_LEDCFG2;
		break;

	case LED_PIN_GPIO0:
	default:
		break;
	}

	RT_TRACE(rtlpriv, COMP_LED, DBG_LOUD,
		 "In SwLedOff,LedAddr:%X LEDPIN=%d\n",
		 ledreg, pled->ledpin);

	if (pcipriv->ledctl.led_opendrain) {
		u8 ledcfg = rtl_read_byte(rtlpriv, ledreg);

		ledreg &= 0xd0;
		rtl_write_byte(rtlpriv, ledreg, (ledcfg | BIT(3)));


		ledcfg = rtl_read_byte(rtlpriv, REG_MAC_PINMUX_CFG);
		ledcfg &= 0xFE;
		rtl_write_byte(rtlpriv, REG_MAC_PINMUX_CFG, ledcfg);
	} else {
		rtl_write_byte(rtlpriv, ledreg, 0x28);
	}

	pled->ledon = false;
}
