pair_to_flags (const char *str)
{
	g_return_val_if_fail (str != NULL, NM_802_11_AP_SEC_NONE);

	if (strcmp (str, "wep40") == 0)
		return NM_802_11_AP_SEC_PAIR_WEP40;
	if (strcmp (str, "wep104") == 0)
		return NM_802_11_AP_SEC_PAIR_WEP104;
	if (strcmp (str, "tkip") == 0)
		return NM_802_11_AP_SEC_PAIR_TKIP;
	if (strcmp (str, "ccmp") == 0)
		return NM_802_11_AP_SEC_PAIR_CCMP;
	return NM_802_11_AP_SEC_NONE;
}
