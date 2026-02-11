send_delba(struct adapter *padapter, u8 initiator, u8 *addr)
{
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct sta_info *psta = NULL;

	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	u16 tid;

	if ((pmlmeinfo->state&0x03) != WIFI_FW_AP_STATE)
		if (!(pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS))
			return _SUCCESS;

	psta = rtw_get_stainfo(pstapriv, addr);
	if (psta == NULL)
		return _SUCCESS;

	if (initiator == 0) {
		for (tid = 0; tid < MAXTID; tid++) {
			if (psta->recvreorder_ctrl[tid].enable) {
				DBG_88E("rx agg disable tid(%d)\n", tid);
				issue_action_BA(padapter, addr, RTW_WLAN_ACTION_DELBA, (((tid << 1) | initiator)&0x1F));
				psta->recvreorder_ctrl[tid].enable = false;
				psta->recvreorder_ctrl[tid].indicate_seq = 0xffff;
			}
		}
	} else if (initiator == 1) {
		for (tid = 0; tid < MAXTID; tid++) {
			if (psta->htpriv.agg_enable_bitmap & BIT(tid)) {
				DBG_88E("tx agg disable tid(%d)\n", tid);
				issue_action_BA(padapter, addr, RTW_WLAN_ACTION_DELBA, (((tid << 1) | initiator)&0x1F));
				psta->htpriv.agg_enable_bitmap &= ~BIT(tid);
				psta->htpriv.candidate_tid_bitmap &= ~BIT(tid);
			}
		}
	}

	return _SUCCESS;
}
