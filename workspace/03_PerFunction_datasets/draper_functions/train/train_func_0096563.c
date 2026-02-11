carl9170_init_power_cal(struct ar9170 *ar)
{
	carl9170_regwrite_begin(ar);

	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE_MAX, 0x7f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE1, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE2, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE3, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE4, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE5, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE6, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE7, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE8, 0x3f3f3f3f);
	carl9170_regwrite(AR9170_PHY_REG_POWER_TX_RATE9, 0x3f3f3f3f);

	carl9170_regwrite_finish();
	return carl9170_regwrite_result();
}
