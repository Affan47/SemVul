mwifiex_send_domain_info_cmd_fw(struct wiphy *wiphy)
{
	u8 no_of_triplet = 0;
	struct ieee80211_country_ie_triplet *t;
	u8 no_of_parsed_chan = 0;
	u8 first_chan = 0, next_chan = 0, max_pwr = 0;
	u8 i, flag = 0;
	enum ieee80211_band band;
	struct ieee80211_supported_band *sband;
	struct ieee80211_channel *ch;
	struct mwifiex_adapter *adapter = mwifiex_cfg80211_get_adapter(wiphy);
	struct mwifiex_private *priv;
	struct mwifiex_802_11d_domain_reg *domain_info = &adapter->domain_reg;


	domain_info->country_code[0] = adapter->country_code[0];
	domain_info->country_code[1] = adapter->country_code[1];
	domain_info->country_code[2] = ' ';

	band = mwifiex_band_to_radio_type(adapter->config_bands);
	if (!wiphy->bands[band]) {
		mwifiex_dbg(adapter, ERROR,
			    "11D: setting domain info in FW\n");
		return -1;
	}

	sband = wiphy->bands[band];

	for (i = 0; i < sband->n_channels ; i++) {
		ch = &sband->channels[i];
		if (ch->flags & IEEE80211_CHAN_DISABLED)
			continue;

		if (!flag) {
			flag = 1;
			first_chan = (u32) ch->hw_value;
			next_chan = first_chan;
			max_pwr = ch->max_power;
			no_of_parsed_chan = 1;
			continue;
		}

		if (ch->hw_value == next_chan + 1 &&
		    ch->max_power == max_pwr) {
			next_chan++;
			no_of_parsed_chan++;
		} else {
			t = &domain_info->triplet[no_of_triplet];
			t->chans.first_channel = first_chan;
			t->chans.num_channels = no_of_parsed_chan;
			t->chans.max_power = max_pwr;
			no_of_triplet++;
			first_chan = (u32) ch->hw_value;
			next_chan = first_chan;
			max_pwr = ch->max_power;
			no_of_parsed_chan = 1;
		}
	}

	if (flag) {
		t = &domain_info->triplet[no_of_triplet];
		t->chans.first_channel = first_chan;
		t->chans.num_channels = no_of_parsed_chan;
		t->chans.max_power = max_pwr;
		no_of_triplet++;
	}

	domain_info->no_of_triplet = no_of_triplet;

	priv = mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);

	if (mwifiex_send_cmd(priv, HostCmd_CMD_802_11D_DOMAIN_INFO,
			     HostCmd_ACT_GEN_SET, 0, NULL, false)) {
		mwifiex_dbg(adapter, INFO,
			    "11D: setting domain info in FW\n");
		return -1;
	}

	return 0;
}
