update_BCNTIM(struct adapter *padapter)
{
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	struct wlan_bssid_ex *pnetwork_mlmeext = &(pmlmeinfo->network);
	unsigned char *pie = pnetwork_mlmeext->IEs;


	if (true) {
		u8 *p, *dst_ie, *premainder_ie = NULL;
		u8 *pbackup_remainder_ie = NULL;
		uint offset, tmp_len, tim_ielen, tim_ie_offset, remainder_ielen;

		p = rtw_get_ie(pie + _FIXED_IE_LENGTH_, _TIM_IE_, &tim_ielen,
				pnetwork_mlmeext->IELength - _FIXED_IE_LENGTH_);
		if (p != NULL && tim_ielen > 0) {
			tim_ielen += 2;
			premainder_ie = p+tim_ielen;
			tim_ie_offset = (int)(p - pie);
			remainder_ielen = pnetwork_mlmeext->IELength -
						tim_ie_offset - tim_ielen;

			dst_ie = p;
		} else {
			tim_ielen = 0;


			offset = _FIXED_IE_LENGTH_;
			offset += pnetwork_mlmeext->Ssid.SsidLength + 2;


			p = rtw_get_ie(pie + _BEACON_IE_OFFSET_,
					_SUPPORTEDRATES_IE_, &tmp_len,
					(pnetwork_mlmeext->IELength -
						_BEACON_IE_OFFSET_));
			if (p !=  NULL)
				offset += tmp_len+2;


			offset += 3;

			premainder_ie = pie + offset;

			remainder_ielen = pnetwork_mlmeext->IELength -
						offset - tim_ielen;


			dst_ie = pie + offset;
		}

		if (remainder_ielen > 0) {
			pbackup_remainder_ie = rtw_malloc(remainder_ielen);
			if (pbackup_remainder_ie && premainder_ie)
				memcpy(pbackup_remainder_ie,
						premainder_ie, remainder_ielen);
		}
		*dst_ie++ = _TIM_IE_;

		if ((pstapriv->tim_bitmap&0xff00) &&
				(pstapriv->tim_bitmap&0x00fc))
			tim_ielen = 5;
		else
			tim_ielen = 4;

		*dst_ie++ = tim_ielen;

		*dst_ie++ = 0;
		*dst_ie++ = 1;

		if (pstapriv->tim_bitmap&BIT(0))
			*dst_ie++ = BIT(0);
		else
			*dst_ie++ = 0;

		if (tim_ielen == 4) {
			*dst_ie++ = pstapriv->tim_bitmap & 0xff;
		} else if (tim_ielen == 5) {
			put_unaligned_le16(pstapriv->tim_bitmap, dst_ie);
			dst_ie += 2;
		}


		if (pbackup_remainder_ie) {
			memcpy(dst_ie, pbackup_remainder_ie, remainder_ielen);

			kfree(pbackup_remainder_ie);
		}
		offset =  (uint)(dst_ie - pie);
		pnetwork_mlmeext->IELength = offset + remainder_ielen;
	}

	set_tx_beacon_cmd(padapter);
}
