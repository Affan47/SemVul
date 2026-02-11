rtl8723a_mlme_sitesurvey(struct rtw_adapter *padapter, u8 flag)
{
	if (flag) {
		u32 v32;


		v32 = rtl8723au_read32(padapter, REG_RCR);
		v32 &= ~(RCR_CBSSID_BCN);
		rtl8723au_write32(padapter, REG_RCR, v32);

		rtl8723au_write16(padapter, REG_RXFLTMAP2, 0);


		SetBcnCtrlReg23a(padapter, DIS_TSF_UDT, 0);
	} else {

		struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
		struct mlme_ext_info *pmlmeinfo;
		u32 v32;

		pmlmeinfo = &pmlmeext->mlmext_info;

		if ((is_client_associated_to_ap23a(padapter) == true) ||
		    ((pmlmeinfo->state & 0x03) == MSR_ADHOC) ||
		    ((pmlmeinfo->state & 0x03) == MSR_AP)) {

			rtl8723au_write16(padapter, REG_RXFLTMAP2, 0xFFFF);


			SetBcnCtrlReg23a(padapter, 0, DIS_TSF_UDT);
		}

		v32 = rtl8723au_read32(padapter, REG_RCR);
		v32 |= RCR_CBSSID_BCN;
		rtl8723au_write32(padapter, REG_RCR, v32);
	}

	rtl8723a_BT_wifiscan_notify(padapter, flag ? true : false);
}
