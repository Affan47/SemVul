send_association_request(struct atmel_private *priv, int is_reassoc)
{
	u8 *ssid_el_p;
	int bodysize;
	struct ieee80211_hdr header;
	struct ass_req_format {
		__le16 capability;
		__le16 listen_interval;
		u8 ap[ETH_ALEN];
		u8 ssid_el_id;
		u8 ssid_len;
		u8 ssid[MAX_SSID_LENGTH];
		u8 sup_rates_el_id;
		u8 sup_rates_len;
		u8 rates[4];
	} body;

	header.frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
		(is_reassoc ? IEEE80211_STYPE_REASSOC_REQ : IEEE80211_STYPE_ASSOC_REQ));
	header.duration_id = cpu_to_le16(0x8000);
	header.seq_ctrl = 0;

	memcpy(header.addr1, priv->CurrentBSSID, ETH_ALEN);
	memcpy(header.addr2, priv->dev->dev_addr, ETH_ALEN);
	memcpy(header.addr3, priv->CurrentBSSID, ETH_ALEN);

	body.capability = cpu_to_le16(WLAN_CAPABILITY_ESS);
	if (priv->wep_is_on)
		body.capability |= cpu_to_le16(WLAN_CAPABILITY_PRIVACY);
	if (priv->preamble == SHORT_PREAMBLE)
		body.capability |= cpu_to_le16(WLAN_CAPABILITY_SHORT_PREAMBLE);

	body.listen_interval = cpu_to_le16(priv->listen_interval * priv->beacon_period);


	if (is_reassoc) {
		memcpy(body.ap, priv->CurrentBSSID, ETH_ALEN);
		ssid_el_p = &body.ssid_el_id;
		bodysize = 18 + priv->SSID_size;
	} else {
		ssid_el_p = &body.ap[0];
		bodysize = 12 + priv->SSID_size;
	}

	ssid_el_p[0] = WLAN_EID_SSID;
	ssid_el_p[1] = priv->SSID_size;
	memcpy(ssid_el_p + 2, priv->SSID, priv->SSID_size);
	ssid_el_p[2 + priv->SSID_size] = WLAN_EID_SUPP_RATES;
	ssid_el_p[3 + priv->SSID_size] = 4;
	memcpy(ssid_el_p + 4 + priv->SSID_size, atmel_basic_rates, 4);

	atmel_transmit_management_frame(priv, &header, (void *)&body, bodysize);
}
