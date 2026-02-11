brcms_c_channel_min_txpower_limits_with_local_constraint(
		struct brcms_cm_info *wlc_cm, struct txpwr_limits *txpwr,
		u8 local_constraint_qdbm)
{
	int j;


	for (j = 0; j < WL_TX_POWER_CCK_NUM; j++)
		txpwr->cck[j] = min(txpwr->cck[j], local_constraint_qdbm);


	for (j = 0; j < WL_TX_POWER_OFDM_NUM; j++)
		txpwr->ofdm[j] = min(txpwr->ofdm[j], local_constraint_qdbm);


	for (j = 0; j < BRCMS_NUM_RATES_OFDM; j++)
		txpwr->ofdm_cdd[j] =
		    min(txpwr->ofdm_cdd[j], local_constraint_qdbm);


	for (j = 0; j < BRCMS_NUM_RATES_OFDM; j++)
		txpwr->ofdm_40_siso[j] =
		    min(txpwr->ofdm_40_siso[j], local_constraint_qdbm);


	for (j = 0; j < BRCMS_NUM_RATES_OFDM; j++)
		txpwr->ofdm_40_cdd[j] =
		    min(txpwr->ofdm_40_cdd[j], local_constraint_qdbm);


	for (j = 0; j < BRCMS_NUM_RATES_MCS_1_STREAM; j++)
		txpwr->mcs_20_siso[j] =
		    min(txpwr->mcs_20_siso[j], local_constraint_qdbm);


	for (j = 0; j < BRCMS_NUM_RATES_MCS_1_STREAM; j++)
		txpwr->mcs_20_cdd[j] =
		    min(txpwr->mcs_20_cdd[j], local_constraint_qdbm);


	for (j = 0; j < BRCMS_NUM_RATES_MCS_1_STREAM; j++)
		txpwr->mcs_20_stbc[j] =
		    min(txpwr->mcs_20_stbc[j], local_constraint_qdbm);


	for (j = 0; j < BRCMS_NUM_RATES_MCS_2_STREAM; j++)
		txpwr->mcs_20_mimo[j] =
		    min(txpwr->mcs_20_mimo[j], local_constraint_qdbm);


	for (j = 0; j < BRCMS_NUM_RATES_MCS_1_STREAM; j++)
		txpwr->mcs_40_siso[j] =
		    min(txpwr->mcs_40_siso[j], local_constraint_qdbm);


	for (j = 0; j < BRCMS_NUM_RATES_MCS_1_STREAM; j++)
		txpwr->mcs_40_cdd[j] =
		    min(txpwr->mcs_40_cdd[j], local_constraint_qdbm);


	for (j = 0; j < BRCMS_NUM_RATES_MCS_1_STREAM; j++)
		txpwr->mcs_40_stbc[j] =
		    min(txpwr->mcs_40_stbc[j], local_constraint_qdbm);


	for (j = 0; j < BRCMS_NUM_RATES_MCS_2_STREAM; j++)
		txpwr->mcs_40_mimo[j] =
		    min(txpwr->mcs_40_mimo[j], local_constraint_qdbm);


	txpwr->mcs32 = min(txpwr->mcs32, local_constraint_qdbm);

}
