ar9003_hw_spur_mitigate_mrc_cck(struct ath_hw *ah,
					    struct ath9k_channel *chan)
{
	static const u32 spur_freq[4] = { 2420, 2440, 2464, 2480 };
	int cur_bb_spur, negative = 0, cck_spur_freq;
	int i;
	int range, max_spur_cnts, synth_freq;
	u8 *spur_fbin_ptr = ar9003_get_spur_chan_ptr(ah, IS_CHAN_2GHZ(chan));


	if (AR_SREV_9485(ah) || AR_SREV_9340(ah) || AR_SREV_9330(ah) ||
	    AR_SREV_9550(ah) || AR_SREV_9561(ah)) {
		if (spur_fbin_ptr[0] == 0)
			return;
		max_spur_cnts = 5;
		if (IS_CHAN_HT40(chan)) {
			range = 19;
			if (REG_READ_FIELD(ah, AR_PHY_GEN_CTRL,
					   AR_PHY_GC_DYN2040_PRI_CH) == 0)
				synth_freq = chan->channel + 10;
			else
				synth_freq = chan->channel - 10;
		} else {
			range = 10;
			synth_freq = chan->channel;
		}
	} else {
		range = AR_SREV_9462(ah) ? 5 : 10;
		max_spur_cnts = 4;
		synth_freq = chan->channel;
	}

	for (i = 0; i < max_spur_cnts; i++) {
		if (AR_SREV_9462(ah) && (i == 0 || i == 3))
			continue;

		negative = 0;
		if (AR_SREV_9485(ah) || AR_SREV_9340(ah) || AR_SREV_9330(ah) ||
		    AR_SREV_9550(ah) || AR_SREV_9561(ah))
			cur_bb_spur = ath9k_hw_fbin2freq(spur_fbin_ptr[i],
							 IS_CHAN_2GHZ(chan));
		else
			cur_bb_spur = spur_freq[i];

		cur_bb_spur -= synth_freq;
		if (cur_bb_spur < 0) {
			negative = 1;
			cur_bb_spur = -cur_bb_spur;
		}
		if (cur_bb_spur < range) {
			cck_spur_freq = (int)((cur_bb_spur << 19) / 11);

			if (negative == 1)
				cck_spur_freq = -cck_spur_freq;

			cck_spur_freq = cck_spur_freq & 0xfffff;

			REG_RMW_FIELD(ah, AR_PHY_AGC_CONTROL,
				      AR_PHY_AGC_CONTROL_YCOK_MAX, 0x7);
			REG_RMW_FIELD(ah, AR_PHY_CCK_SPUR_MIT,
				      AR_PHY_CCK_SPUR_MIT_SPUR_RSSI_THR, 0x7f);
			REG_RMW_FIELD(ah, AR_PHY_CCK_SPUR_MIT,
				      AR_PHY_CCK_SPUR_MIT_SPUR_FILTER_TYPE,
				      0x2);
			REG_RMW_FIELD(ah, AR_PHY_CCK_SPUR_MIT,
				      AR_PHY_CCK_SPUR_MIT_USE_CCK_SPUR_MIT,
				      0x1);
			REG_RMW_FIELD(ah, AR_PHY_CCK_SPUR_MIT,
				      AR_PHY_CCK_SPUR_MIT_CCK_SPUR_FREQ,
				      cck_spur_freq);

			return;
		}
	}

	REG_RMW_FIELD(ah, AR_PHY_AGC_CONTROL,
		      AR_PHY_AGC_CONTROL_YCOK_MAX, 0x5);
	REG_RMW_FIELD(ah, AR_PHY_CCK_SPUR_MIT,
		      AR_PHY_CCK_SPUR_MIT_USE_CCK_SPUR_MIT, 0x0);
	REG_RMW_FIELD(ah, AR_PHY_CCK_SPUR_MIT,
		      AR_PHY_CCK_SPUR_MIT_CCK_SPUR_FREQ, 0x0);
}
