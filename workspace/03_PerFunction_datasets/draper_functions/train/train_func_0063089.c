prep_mac80211_status(struct brcms_c_info *wlc, struct d11rxhdr *rxh,
		     struct sk_buff *p,
		     struct ieee80211_rx_status *rx_status)
{
	int channel;
	u32 rspec;
	unsigned char *plcp;


	rx_status->mactime = brcms_c_recover_tsf64(wlc, rxh);
	rx_status->flag |= RX_FLAG_MACTIME_START;

	channel = BRCMS_CHAN_CHANNEL(rxh->RxChan);

	rx_status->band =
		channel > 14 ? IEEE80211_BAND_5GHZ : IEEE80211_BAND_2GHZ;
	rx_status->freq =
		ieee80211_channel_to_frequency(channel, rx_status->band);

	rx_status->signal = wlc_phy_rssi_compute(wlc->hw->band->pi, rxh);


	rx_status->antenna =
		(rxh->PhyRxStatus_0 & PRXS0_RXANT_UPSUBBAND) ? 1 : 0;

	plcp = p->data;

	rspec = brcms_c_compute_rspec(rxh, plcp);
	if (is_mcs_rate(rspec)) {
		rx_status->rate_idx = rspec & RSPEC_RATE_MASK;
		rx_status->flag |= RX_FLAG_HT;
		if (rspec_is40mhz(rspec))
			rx_status->flag |= RX_FLAG_40MHZ;
	} else {
		switch (rspec2rate(rspec)) {
		case BRCM_RATE_1M:
			rx_status->rate_idx = 0;
			break;
		case BRCM_RATE_2M:
			rx_status->rate_idx = 1;
			break;
		case BRCM_RATE_5M5:
			rx_status->rate_idx = 2;
			break;
		case BRCM_RATE_11M:
			rx_status->rate_idx = 3;
			break;
		case BRCM_RATE_6M:
			rx_status->rate_idx = 4;
			break;
		case BRCM_RATE_9M:
			rx_status->rate_idx = 5;
			break;
		case BRCM_RATE_12M:
			rx_status->rate_idx = 6;
			break;
		case BRCM_RATE_18M:
			rx_status->rate_idx = 7;
			break;
		case BRCM_RATE_24M:
			rx_status->rate_idx = 8;
			break;
		case BRCM_RATE_36M:
			rx_status->rate_idx = 9;
			break;
		case BRCM_RATE_48M:
			rx_status->rate_idx = 10;
			break;
		case BRCM_RATE_54M:
			rx_status->rate_idx = 11;
			break;
		default:
			brcms_err(wlc->hw->d11core,
				  "%s: Unknown rate\n", __func__);
		}


		if (rx_status->band == IEEE80211_BAND_5GHZ)
			rx_status->rate_idx -= BRCMS_LEGACY_5G_RATE_OFFSET;


		if (is_cck_rate(rspec)) {
			if (rxh->PhyRxStatus_0 & PRXS0_SHORTH)
				rx_status->flag |= RX_FLAG_SHORTPRE;
		} else if (is_ofdm_rate(rspec)) {
			rx_status->flag |= RX_FLAG_SHORTPRE;
		} else {
			brcms_err(wlc->hw->d11core, "%s: Unknown modulation\n",
				  __func__);
		}
	}

	if (plcp3_issgi(plcp[3]))
		rx_status->flag |= RX_FLAG_SHORT_GI;

	if (rxh->RxStatus1 & RXS_DECERR) {
		rx_status->flag |= RX_FLAG_FAILED_PLCP_CRC;
		brcms_err(wlc->hw->d11core, "%s:  RX_FLAG_FAILED_PLCP_CRC\n",
			  __func__);
	}
	if (rxh->RxStatus1 & RXS_FCSERR) {
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
		brcms_err(wlc->hw->d11core, "%s:  RX_FLAG_FAILED_FCS_CRC\n",
			  __func__);
	}
}
