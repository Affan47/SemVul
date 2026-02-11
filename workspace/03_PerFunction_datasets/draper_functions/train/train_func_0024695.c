rtw_cfg80211_set_wpa_version(struct security_priv *psecuritypriv,
					u32 wpa_version)
{
	DBG_8723A("%s, wpa_version =%d\n", __func__, wpa_version);

	if (!wpa_version) {
		psecuritypriv->ndisauthtype = Ndis802_11AuthModeOpen;
		return 0;
	}

	if (wpa_version & (NL80211_WPA_VERSION_1 | NL80211_WPA_VERSION_2))
		psecuritypriv->ndisauthtype = Ndis802_11AuthModeWPAPSK;


	return 0;
}
