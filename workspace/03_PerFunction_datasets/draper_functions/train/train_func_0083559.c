b43legacy_write_beacon_template(struct b43legacy_wldev *dev,
					    u16 ram_offset,
					    u16 shm_size_offset)
{

	unsigned int i, len, variable_len;
	const struct ieee80211_mgmt *bcn;
	const u8 *ie;
	bool tim_found = false;
	unsigned int rate;
	u16 ctl;
	int antenna;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(dev->wl->current_beacon);

	bcn = (const struct ieee80211_mgmt *)(dev->wl->current_beacon->data);
	len = min_t(size_t, dev->wl->current_beacon->len,
		  0x200 - sizeof(struct b43legacy_plcp_hdr6));
	rate = ieee80211_get_tx_rate(dev->wl->hw, info)->hw_value;

	b43legacy_write_template_common(dev, (const u8 *)bcn, len, ram_offset,
					shm_size_offset, rate);


	antenna = B43legacy_ANTENNA_DEFAULT;
	antenna = b43legacy_antenna_to_phyctl(antenna);
	ctl = b43legacy_shm_read16(dev, B43legacy_SHM_SHARED,
				   B43legacy_SHM_SH_BEACPHYCTL);

	ctl &= ~B43legacy_TX4_PHY_SHORTPRMBL;
	ctl &= ~B43legacy_TX4_PHY_ANT;
	ctl &= ~B43legacy_TX4_PHY_ENC;
	ctl |= antenna;
	ctl |= B43legacy_TX4_PHY_ENC_CCK;
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_BEACPHYCTL, ctl);


	ie = bcn->u.beacon.variable;
	variable_len = len - offsetof(struct ieee80211_mgmt, u.beacon.variable);
	for (i = 0; i < variable_len - 2; ) {
		uint8_t ie_id, ie_len;

		ie_id = ie[i];
		ie_len = ie[i + 1];
		if (ie_id == 5) {
			u16 tim_position;
			u16 dtim_period;


			if (variable_len < ie_len + 2 + i)
				break;

			if (ie_len < 4)
				break;
			tim_found = true;

			tim_position = sizeof(struct b43legacy_plcp_hdr6);
			tim_position += offsetof(struct ieee80211_mgmt,
						 u.beacon.variable);
			tim_position += i;

			dtim_period = ie[i + 3];

			b43legacy_shm_write16(dev, B43legacy_SHM_SHARED,
					B43legacy_SHM_SH_TIMPOS, tim_position);
			b43legacy_shm_write16(dev, B43legacy_SHM_SHARED,
					B43legacy_SHM_SH_DTIMP, dtim_period);
			break;
		}
		i += ie_len + 2;
	}
	if (!tim_found) {
		b43legacywarn(dev->wl, "Did not find a valid TIM IE in the "
			      "beacon template packet. AP or IBSS operation "
			      "may be broken.\n");
	} else
		b43legacydbg(dev->wl, "Updated beacon template\n");
}
