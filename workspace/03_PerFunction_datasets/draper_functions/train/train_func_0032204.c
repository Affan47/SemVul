ath5k_hw_proc_4word_tx_status(struct ath5k_hw *ah __unused,
		struct ath5k_desc *desc, struct ath5k_tx_status *ts)
{
	struct ath5k_hw_4w_tx_ctl *tx_ctl;
	struct ath5k_hw_tx_status *tx_status;

	tx_ctl = &desc->ud.ds_tx5212.tx_ctl;
	tx_status = &desc->ud.ds_tx5212.tx_stat;


	if (!(tx_status->tx_status_1 & AR5K_DESC_TX_STATUS1_DONE))
		return -EINPROGRESS;


	ts->ts_tstamp = AR5K_REG_MS(tx_status->tx_status_0,
		AR5K_DESC_TX_STATUS0_SEND_TIMESTAMP);
	ts->ts_shortretry = AR5K_REG_MS(tx_status->tx_status_0,
		AR5K_DESC_TX_STATUS0_SHORT_RETRY_COUNT);
	ts->ts_longretry = AR5K_REG_MS(tx_status->tx_status_0,
		AR5K_DESC_TX_STATUS0_LONG_RETRY_COUNT);
	ts->ts_seqnum = AR5K_REG_MS(tx_status->tx_status_1,
		AR5K_DESC_TX_STATUS1_SEQ_NUM);
	ts->ts_rssi = AR5K_REG_MS(tx_status->tx_status_1,
		AR5K_DESC_TX_STATUS1_ACK_SIG_STRENGTH);
	ts->ts_antenna = (tx_status->tx_status_1 &
		AR5K_DESC_TX_STATUS1_XMIT_ANTENNA) ? 2 : 1;
	ts->ts_status = 0;

	ts->ts_final_idx = AR5K_REG_MS(tx_status->tx_status_1,
			AR5K_DESC_TX_STATUS1_FINAL_TS_INDEX);

	ts->ts_retry[0] = ts->ts_longretry;
	ts->ts_rate[0] = tx_ctl->tx_control_3 &
		AR5K_4W_TX_DESC_CTL3_XMIT_RATE0;


	if (!(tx_status->tx_status_0 & AR5K_DESC_TX_STATUS0_FRAME_XMIT_OK)) {
		if (tx_status->tx_status_0 &
				AR5K_DESC_TX_STATUS0_EXCESSIVE_RETRIES)
			ts->ts_status |= AR5K_TXERR_XRETRY;

		if (tx_status->tx_status_0 & AR5K_DESC_TX_STATUS0_FIFO_UNDERRUN)
			ts->ts_status |= AR5K_TXERR_FIFO;

		if (tx_status->tx_status_0 & AR5K_DESC_TX_STATUS0_FILTERED)
			ts->ts_status |= AR5K_TXERR_FILT;
	}

	return 0;
}
