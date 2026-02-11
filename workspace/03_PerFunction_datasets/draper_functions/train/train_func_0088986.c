update_bcn_wps_ie(struct adapter *padapter)
{
	u8 *pwps_ie = NULL, *pwps_ie_src;
	u8 *premainder_ie, *pbackup_remainder_ie = NULL;
	uint wps_ielen = 0, wps_offset, remainder_ielen;
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	struct wlan_bssid_ex *pnetwork = &(pmlmeinfo->network);
	unsigned char *ie = pnetwork->IEs;
	u32 ielen = pnetwork->IELength;

	DBG_88E("%s\n", __func__);

	pwps_ie_src = pmlmepriv->wps_beacon_ie;
	if (pwps_ie_src == NULL)
		return;

	pwps_ie = rtw_get_wps_ie(ie+_FIXED_IE_LENGTH_, ielen-_FIXED_IE_LENGTH_, NULL, &wps_ielen);

	if (pwps_ie == NULL || wps_ielen == 0)
		return;

	wps_offset = (uint)(pwps_ie-ie);

	premainder_ie = pwps_ie + wps_ielen;

	remainder_ielen = ielen - wps_offset - wps_ielen;

	if (remainder_ielen > 0) {
		pbackup_remainder_ie = rtw_malloc(remainder_ielen);
		if (pbackup_remainder_ie)
			memcpy(pbackup_remainder_ie, premainder_ie, remainder_ielen);
	}

	wps_ielen = (uint)pwps_ie_src[1];
	if ((wps_offset+wps_ielen+2+remainder_ielen) <= MAX_IE_SZ) {
		memcpy(pwps_ie, pwps_ie_src, wps_ielen+2);
		pwps_ie += (wps_ielen+2);

		if (pbackup_remainder_ie)
			memcpy(pwps_ie, pbackup_remainder_ie, remainder_ielen);


		pnetwork->IELength = wps_offset + (wps_ielen+2) + remainder_ielen;
	}

	kfree(pbackup_remainder_ie);
}
