ath9k_hw_cfg_gpio_input(struct ath_hw *ah, u32 gpio)
{
	u32 gpio_shift;

	BUG_ON(gpio >= ah->caps.num_gpio_pins);

	if (AR_DEVID_7010(ah)) {
		gpio_shift = gpio;
		REG_RMW(ah, AR7010_GPIO_OE,
			(AR7010_GPIO_OE_AS_INPUT << gpio_shift),
			(AR7010_GPIO_OE_MASK << gpio_shift));
		return;
	}

	gpio_shift = gpio << 1;
	REG_RMW(ah,
		AR_GPIO_OE_OUT,
		(AR_GPIO_OE_OUT_DRV_NO << gpio_shift),
		(AR_GPIO_OE_OUT_DRV << gpio_shift));
}
