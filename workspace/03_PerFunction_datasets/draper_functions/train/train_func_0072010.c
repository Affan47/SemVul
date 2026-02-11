getpowerbase88e(struct adapter *adapt, u8 *pwr_level_ofdm,
			    u8 *pwr_level_bw20, u8 *pwr_level_bw40,
			    u8 channel, u32 *ofdmbase, u32 *mcs_base)
{
	struct hal_data_8188e *hal_data = GET_HAL_DATA(adapt);
	u32 powerbase0, powerbase1;
	u8 i, powerlevel[2];

	for (i = 0; i < 2; i++) {
		powerbase0 = pwr_level_ofdm[i];

		powerbase0 = (powerbase0<<24) | (powerbase0<<16) |
			     (powerbase0<<8) | powerbase0;
		*(ofdmbase+i) = powerbase0;
	}
	for (i = 0; i < hal_data->NumTotalRFPath; i++) {

		if (hal_data->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
			powerlevel[i] = pwr_level_bw20[i];
		else
			powerlevel[i] = pwr_level_bw40[i];
		powerbase1 = powerlevel[i];
		powerbase1 = (powerbase1<<24) | (powerbase1<<16) |
			     (powerbase1<<8) | powerbase1;
		*(mcs_base+i) = powerbase1;
	}
}
