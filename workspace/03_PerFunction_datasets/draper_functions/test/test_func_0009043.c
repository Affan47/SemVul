retrieve_bss(struct atmel_private *priv)
{
	int i;
	int max_rssi = -128;
	int max_index = -1;

	if (priv->BSS_list_entries == 0)
		return -1;

	if (priv->connect_to_any_BSS) {


		priv->current_BSS = 0;
		for (i = 0; i < priv->BSS_list_entries; i++) {
			if (priv->operating_mode == priv->BSSinfo[i].BSStype &&
			    ((!priv->wep_is_on && !priv->BSSinfo[i].UsingWEP) ||
			     (priv->wep_is_on && priv->BSSinfo[i].UsingWEP)) &&
			    !(priv->BSSinfo[i].channel & 0x80)) {
				max_rssi = priv->BSSinfo[i].RSSI;
				priv->current_BSS = max_index = i;
			}
		}
		return max_index;
	}

	for (i = 0; i < priv->BSS_list_entries; i++) {
		if (priv->SSID_size == priv->BSSinfo[i].SSIDsize &&
		    memcmp(priv->SSID, priv->BSSinfo[i].SSID, priv->SSID_size) == 0 &&
		    priv->operating_mode == priv->BSSinfo[i].BSStype &&
		    atmel_validate_channel(priv, priv->BSSinfo[i].channel) == 0) {
			if (priv->BSSinfo[i].RSSI >= max_rssi) {
				max_rssi = priv->BSSinfo[i].RSSI;
				max_index = i;
			}
		}
	}
	return max_index;
}
