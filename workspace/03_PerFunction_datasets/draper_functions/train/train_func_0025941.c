AddWepKey(mac_addr bssid, uint8_t *key, unsigned int len,
									int temp) {
	if (len > WEPKEY_MAX)
		return;

    wep_key_info *winfo = new wep_key_info;

	winfo->decrypted = 0;
	winfo->failed = 0;
    winfo->bssid = bssid;
	winfo->fragile = temp;
    winfo->len = len;

    memcpy(winfo->key, key, len);


	if (wepkeys.find(winfo->bssid) != wepkeys.end()) {
		delete wepkeys[winfo->bssid];
		wepkeys[winfo->bssid] = winfo;
		return;
	}

	wepkeys.insert(winfo->bssid, winfo);
}
