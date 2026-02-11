update_bmc_sta(struct adapter *padapter)
{
	u32 init_rate = 0;
	unsigned char	network_type, raid;
	int i, supportRateNum = 0;
	unsigned int tx_ra_bitmap = 0;
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	struct wlan_bssid_ex *pcur_network = (struct wlan_bssid_ex *)&pmlmepriv->cur_network.network;
	struct sta_info *psta = rtw_get_bcmc_stainfo(padapter);

	if (psta) {
		psta->aid = 0;
		psta->mac_id = psta->aid + 1;

		psta->qos_option = 0;
		psta->htpriv.ht_option = false;

		psta->ieee8021x_blocked = 0;

		memset((void *)&psta->sta_stats, 0, sizeof(struct stainfo_stats));


		supportRateNum = rtw_get_rateset_len((u8 *)&pcur_network->SupportedRates);
		network_type = rtw_check_network_type((u8 *)&pcur_network->SupportedRates, supportRateNum, 1);

		memcpy(psta->bssrateset, &pcur_network->SupportedRates, supportRateNum);
		psta->bssratelen = supportRateNum;


		for (i = 0; i < supportRateNum; i++) {
			if (psta->bssrateset[i])
				tx_ra_bitmap |= rtw_get_bit_value_from_ieee_value(psta->bssrateset[i]&0x7f);
		}

		if (pcur_network->Configuration.DSConfig > 14) {

			network_type = WIRELESS_11A;
			tx_ra_bitmap = 0x150;
		} else {

			network_type = WIRELESS_11B;
			tx_ra_bitmap = 0xf;
		}

		raid = networktype_to_raid(network_type);
		init_rate = get_highest_rate_idx(tx_ra_bitmap&0x0fffffff)&0x3f;


		rtw_hal_set_odm_var(padapter, HAL_ODM_STA_INFO, psta, true);

		{
			u8 arg = 0;

			arg = psta->mac_id&0x1f;
			arg |= BIT(7);
			tx_ra_bitmap |= ((raid<<28)&0xf0000000);
			DBG_88E("update_bmc_sta, mask = 0x%x, arg = 0x%x\n", tx_ra_bitmap, arg);


			rtw_hal_add_ra_tid(padapter, tx_ra_bitmap, arg, 0);
		}

		psta->raid = raid;
		psta->init_rate = init_rate;

		rtw_stassoc_hw_rpt(padapter, psta);

		spin_lock_bh(&psta->lock);
		psta->state = _FW_LINKED;
		spin_unlock_bh(&psta->lock);

	} else {
		DBG_88E("add_RATid_bmc_sta error!\n");
	}
}
