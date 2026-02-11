ar5008_hw_force_bias(struct ath_hw *ah, u16 synth_freq)
{
	u32 tmp_reg;
	unsigned int reg_writes = 0;
	u32 new_bias = 0;

	if (!AR_SREV_5416(ah) || synth_freq >= 3000)
		return;

	if (synth_freq < 2412)
		new_bias = 0;
	else if (synth_freq < 2422)
		new_bias = 1;
	else
		new_bias = 2;


	tmp_reg = ath9k_hw_reverse_bits(new_bias, 3);

	DBG("ath9k: Force rf_pwd_icsyndiv to %1d on %4d\n",
		new_bias, synth_freq);


	ar5008_hw_phy_modify_rx_buffer(ah->analogBank6Data, tmp_reg, 3, 181, 3);


	REG_WRITE_RF_ARRAY(&ah->iniBank6, ah->analogBank6Data, reg_writes);
}
