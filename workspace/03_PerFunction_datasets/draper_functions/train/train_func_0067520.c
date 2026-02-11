ipw_led_band_on(struct ipw_priv *priv)
{
	unsigned long flags;
	u32 led;


	if (priv->config & CFG_NO_LED ||
	    priv->nic_type != EEPROM_NIC_TYPE_1 || !priv->assoc_network)
		return;

	spin_lock_irqsave(&priv->lock, flags);

	led = ipw_read_reg32(priv, IPW_EVENT_REG);
	if (priv->assoc_network->mode == IEEE_A) {
		led |= priv->led_ofdm_on;
		led &= priv->led_association_off;
		IPW_DEBUG_LED("Mode LED On: 802.11a\n");
	} else if (priv->assoc_network->mode == IEEE_G) {
		led |= priv->led_ofdm_on;
		led |= priv->led_association_on;
		IPW_DEBUG_LED("Mode LED On: 802.11g\n");
	} else {
		led &= priv->led_ofdm_off;
		led |= priv->led_association_on;
		IPW_DEBUG_LED("Mode LED On: 802.11b\n");
	}

	led = ipw_register_toggle(led);

	IPW_DEBUG_LED("Reg: 0x%08X\n", led);
	ipw_write_reg32(priv, IPW_EVENT_REG, led);

	spin_unlock_irqrestore(&priv->lock, flags);
}
