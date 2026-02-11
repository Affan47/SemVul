ath9k_hw_btcoex_init_2wire(struct ath_hw *ah)
{
	struct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;


	REG_CLR_BIT(ah, AR_GPIO_INPUT_EN_VAL,
		    (AR_GPIO_INPUT_EN_VAL_BT_PRIORITY_DEF |
		     AR_GPIO_INPUT_EN_VAL_BT_FREQUENCY_DEF));

	REG_SET_BIT(ah, AR_GPIO_INPUT_EN_VAL,
		    AR_GPIO_INPUT_EN_VAL_BT_ACTIVE_BB);


	REG_RMW_FIELD(ah, AR_GPIO_INPUT_MUX1,
		      AR_GPIO_INPUT_MUX1_BT_ACTIVE,
		      btcoex_hw->btactive_gpio);


	ath9k_hw_cfg_gpio_input(ah, btcoex_hw->btactive_gpio);
}
