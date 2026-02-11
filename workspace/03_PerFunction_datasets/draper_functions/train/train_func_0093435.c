is_frame_from_current_bss(struct atmel_private *priv,
				     struct ieee80211_hdr *header)
{
	if (le16_to_cpu(header->frame_control) & IEEE80211_FCTL_FROMDS)
		return memcmp(header->addr3, priv->CurrentBSSID, 6) == 0;
	else
		return memcmp(header->addr2, priv->CurrentBSSID, 6) == 0;
}
