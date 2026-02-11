site_survey(struct adapter *padapter)
{
	unsigned char		survey_channel = 0, val8;
	enum rt_scan_type ScanType = SCAN_PASSIVE;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	u32 initialgain = 0;
	struct rtw_ieee80211_channel *ch;

	if (pmlmeext->sitesurvey_res.channel_idx < pmlmeext->sitesurvey_res.ch_num) {
		ch = &pmlmeext->sitesurvey_res.ch[pmlmeext->sitesurvey_res.channel_idx];
		survey_channel = ch->hw_value;
		ScanType = (ch->flags & RTW_IEEE80211_CHAN_PASSIVE_SCAN) ? SCAN_PASSIVE : SCAN_ACTIVE;
	}


	if (survey_channel != 0) {


		if (pmlmeext->sitesurvey_res.channel_idx == 0)
			set_channel_bwmode(padapter, survey_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE, HT_CHANNEL_WIDTH_20);
		else
			SelectChannel(padapter, survey_channel);

		if (ScanType == SCAN_ACTIVE) {
			int i;
			for (i = 0; i < RTW_SSID_SCAN_AMOUNT; i++) {
				if (pmlmeext->sitesurvey_res.ssid[i].SsidLength) {

					issue_probereq(padapter, &(pmlmeext->sitesurvey_res.ssid[i]), NULL);

					issue_probereq(padapter, &(pmlmeext->sitesurvey_res.ssid[i]), NULL);
				}
			}

			if (pmlmeext->sitesurvey_res.scan_mode == SCAN_ACTIVE) {

				issue_probereq(padapter, NULL, NULL);

				issue_probereq(padapter, NULL, NULL);
			}

			if (pmlmeext->sitesurvey_res.scan_mode == SCAN_ACTIVE) {

				issue_probereq(padapter, NULL, NULL);

				issue_probereq(padapter, NULL, NULL);
			}
		}

		set_survey_timer(pmlmeext, pmlmeext->chan_scan_time);
	} else {


		if (rtw_hal_antdiv_before_linked(padapter)) {
			pmlmeext->sitesurvey_res.bss_cnt = 0;
			pmlmeext->sitesurvey_res.channel_idx = -1;
			pmlmeext->chan_scan_time = SURVEY_TO / 2;
			set_survey_timer(pmlmeext, pmlmeext->chan_scan_time);
			return;
		}

		pmlmeext->sitesurvey_res.state = SCAN_COMPLETE;


		set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);


		Set_MSR(padapter, (pmlmeinfo->state & 0x3));

		initialgain = 0xff;
		rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain));

		Restore_DM_Func_Flag(padapter);


		if (is_client_associated_to_ap(padapter))
			issue_nulldata(padapter, NULL, 0, 3, 500);

		val8 = 0;
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_SITESURVEY, (u8 *)(&val8));

		report_surveydone_event(padapter);

		pmlmeext->chan_scan_time = SURVEY_TO;
		pmlmeext->sitesurvey_res.state = SCAN_DISABLE;

		issue_action_BSSCoexistPacket(padapter);
		issue_action_BSSCoexistPacket(padapter);
		issue_action_BSSCoexistPacket(padapter);
	}
	return;
}
