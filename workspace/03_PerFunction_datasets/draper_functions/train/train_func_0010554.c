ath5k_hw_set_gpio_output(struct ath5k_hw *ah, u32 gpio)
{
	if (gpio >= AR5K_NUM_GPIO)
		return -EINVAL;

	ath5k_hw_reg_write(ah,
		(ath5k_hw_reg_read(ah, AR5K_GPIOCR) & ~AR5K_GPIOCR_OUT(gpio))
		| AR5K_GPIOCR_OUT(gpio), AR5K_GPIOCR);

	return 0;
}
