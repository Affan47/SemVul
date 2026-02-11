hw_var_set_correct_tsf(struct rtw_adapter *padapter)
{
	u64 tsf;
	u32 reg_tsftr;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;


	tsf = pmlmeext->TSFValue -
		do_div(pmlmeext->TSFValue,
		       (pmlmeinfo->bcn_interval * 1024)) - 1024;

	if (((pmlmeinfo->state & 0x03) == MSR_ADHOC) ||
	    ((pmlmeinfo->state & 0x03) == MSR_AP)) {


		StopTxBeacon(padapter);
	}

	reg_tsftr = REG_TSFTR;


	SetBcnCtrlReg23a(padapter, 0, EN_BCN_FUNCTION);

	rtl8723au_write32(padapter, reg_tsftr, tsf);
	rtl8723au_write32(padapter, reg_tsftr + 4, tsf >> 32);


	SetBcnCtrlReg23a(padapter, EN_BCN_FUNCTION, 0);

	if (((pmlmeinfo->state & 0x03) == MSR_ADHOC) ||
	    ((pmlmeinfo->state & 0x03) == MSR_AP))
		ResumeTxBeacon(padapter);
}
