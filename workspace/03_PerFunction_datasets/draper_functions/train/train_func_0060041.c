ath5k_hw_request_rfgain_probe(struct ath5k_hw *ah)
{


	if (ah->ah_gain.g_state != AR5K_RFGAIN_ACTIVE)
		return;


	ath5k_hw_reg_write(ah, AR5K_REG_SM(ah->ah_txpower.txp_max_pwr - 4,
			AR5K_PHY_PAPD_PROBE_TXPOWER) |
			AR5K_PHY_PAPD_PROBE_TX_NEXT, AR5K_PHY_PAPD_PROBE);

	ah->ah_gain.g_state = AR5K_RFGAIN_READ_REQUESTED;

}
