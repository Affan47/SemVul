check_bssid_list_item(struct ndis_80211_bssid_ex *bssid,
				  int bssid_len, void *buf, int len)
{
	void *buf_end, *bssid_end;

	if (!bssid || bssid_len <= 0 || bssid_len > len)
		return false;

	buf_end = (char *)buf + len;
	bssid_end = (char *)bssid + bssid_len;

	return (int)(buf_end - bssid_end) >= 0 && (int)(bssid_end - buf) >= 0;
}
