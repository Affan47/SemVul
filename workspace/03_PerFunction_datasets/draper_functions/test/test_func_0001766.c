ar9002_hw_proc_txdesc(struct ath_hw *ah, void *ds,
				 struct ath_tx_status *ts)
{
	struct ar5416_desc *ads = AR5416DESC(ds);
	u32 status;

	status = *(volatile typeof(ads->ds_txstatus9) *)&(ads->ds_txstatus9);
	if ((status & AR_TxDone) == 0)
		return -EINPROGRESS;

	ts->ts_tstamp = ads->AR_SendTimestamp;
	ts->ts_status = 0;
	ts->ts_flags = 0;

	if (status & AR_TxOpExceeded)
		ts->ts_status |= ATH9K_TXERR_XTXOP;
	ts->tid = MS(status, AR_TxTid);
	ts->ts_rateindex = MS(status, AR_FinalTxIdx);
	ts->ts_seqnum = MS(status, AR_SeqNum);

	status = *(volatile typeof(ads->ds_txstatus0) *)&(ads->ds_txstatus0);
	ts->ts_rssi_ctl0 = MS(status, AR_TxRSSIAnt00);
	ts->ts_rssi_ctl1 = MS(status, AR_TxRSSIAnt01);
	ts->ts_rssi_ctl2 = MS(status, AR_TxRSSIAnt02);
	if (status & AR_TxBaStatus) {
		ts->ts_flags |= ATH9K_TX_BA;
		ts->ba_low = ads->AR_BaBitmapLow;
		ts->ba_high = ads->AR_BaBitmapHigh;
	}

	status = *(volatile typeof(ads->ds_txstatus1) *)&(ads->ds_txstatus1);
	if (status & AR_FrmXmitOK)
		ts->ts_status |= ATH9K_TX_ACKED;
	else {
		if (status & AR_ExcessiveRetries)
			ts->ts_status |= ATH9K_TXERR_XRETRY;
		if (status & AR_Filtered)
			ts->ts_status |= ATH9K_TXERR_FILT;
		if (status & AR_FIFOUnderrun) {
			ts->ts_status |= ATH9K_TXERR_FIFO;
			ath9k_hw_updatetxtriglevel(ah, 1);
		}
	}
	if (status & AR_TxTimerExpired)
		ts->ts_status |= ATH9K_TXERR_TIMER_EXPIRED;
	if (status & AR_DescCfgErr)
		ts->ts_flags |= ATH9K_TX_DESC_CFG_ERR;
	if (status & AR_TxDataUnderrun) {
		ts->ts_flags |= ATH9K_TX_DATA_UNDERRUN;
		ath9k_hw_updatetxtriglevel(ah, 1);
	}
	if (status & AR_TxDelimUnderrun) {
		ts->ts_flags |= ATH9K_TX_DELIM_UNDERRUN;
		ath9k_hw_updatetxtriglevel(ah, 1);
	}
	ts->ts_shortretry = MS(status, AR_RTSFailCnt);
	ts->ts_longretry = MS(status, AR_DataFailCnt);
	ts->ts_virtcol = MS(status, AR_VirtRetryCnt);

	status = *(volatile typeof(ads->ds_txstatus5) *)&(ads->ds_txstatus5);
	ts->ts_rssi = MS(status, AR_TxRSSICombined);
	ts->ts_rssi_ext0 = MS(status, AR_TxRSSIAnt10);
	ts->ts_rssi_ext1 = MS(status, AR_TxRSSIAnt11);
	ts->ts_rssi_ext2 = MS(status, AR_TxRSSIAnt12);

	ts->evm0 = ads->AR_TxEVM0;
	ts->evm1 = ads->AR_TxEVM1;
	ts->evm2 = ads->AR_TxEVM2;

	return 0;
}
