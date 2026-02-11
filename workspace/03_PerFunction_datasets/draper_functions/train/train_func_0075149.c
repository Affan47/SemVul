_issue_nulldata23a(struct rtw_adapter *padapter, unsigned char *da,
			      unsigned int power_mode, int wait_ack)
{
	int ret = _FAIL;
	struct xmit_frame *pmgntframe;
	struct pkt_attrib *pattrib;
	unsigned char *pframe;
	struct ieee80211_hdr *pwlanhdr;
	struct xmit_priv *pxmitpriv;
	struct mlme_ext_priv *pmlmeext;
	struct mlme_ext_info *pmlmeinfo;


	if (!padapter)
		goto exit;

	pxmitpriv = &padapter->xmitpriv;
	pmlmeext = &padapter->mlmeextpriv;
	pmlmeinfo = &pmlmeext->mlmext_info;

	pmgntframe = alloc_mgtxmitframe23a(pxmitpriv);
	if (!pmgntframe)
		goto exit;


	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib23a(padapter, pattrib);
	pattrib->retry_ctrl = false;

	memset(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (struct ieee80211_hdr *)pframe;

	pwlanhdr->frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					      IEEE80211_STYPE_NULLFUNC);

	if ((pmlmeinfo->state&0x03) == MSR_AP)
		pwlanhdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_FROMDS);
	else if ((pmlmeinfo->state&0x03) == MSR_INFRA)
		pwlanhdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_TODS);

	if (power_mode)
		pwlanhdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);

	ether_addr_copy(pwlanhdr->addr1, da);
	ether_addr_copy(pwlanhdr->addr2, myid(&padapter->eeprompriv));
	ether_addr_copy(pwlanhdr->addr3, get_my_bssid23a(&pmlmeinfo->network));

	pwlanhdr->seq_ctrl =
		cpu_to_le16(IEEE80211_SN_TO_SEQ(pmlmeext->mgnt_seq));
	pmlmeext->mgnt_seq++;

	pframe += sizeof(struct ieee80211_hdr_3addr);
	pattrib->pktlen = sizeof(struct ieee80211_hdr_3addr);

	pattrib->last_txcmdsz = pattrib->pktlen;

	if (wait_ack)
		ret = dump_mgntframe23a_and_wait_ack23a(padapter, pmgntframe);
	else {
		dump_mgntframe23a(padapter, pmgntframe);
		ret = _SUCCESS;
	}

exit:
	return ret;
}
