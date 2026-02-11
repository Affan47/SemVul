mwifiex_set_ibss_params(struct mwifiex_private *priv,
				   struct cfg80211_ibss_params *params)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	int index = 0, i;
	u8 config_bands = 0;

	if (params->chandef.chan->band == IEEE80211_BAND_2GHZ) {
		if (!params->basic_rates) {
			config_bands = BAND_B | BAND_G;
		} else {
			for (i = 0; i < mwifiex_band_2ghz.n_bitrates; i++) {


				if (mwifiex_rates[i].bitrate == 60) {
					index = 1 << i;
					break;
				}
			}

			if (params->basic_rates < index) {
				config_bands = BAND_B;
			} else {
				config_bands = BAND_G;
				if (params->basic_rates % index)
					config_bands |= BAND_B;
			}
		}

		if (cfg80211_get_chandef_type(&params->chandef) !=
						NL80211_CHAN_NO_HT)
			config_bands |= BAND_G | BAND_GN;
	} else {
		if (cfg80211_get_chandef_type(&params->chandef) ==
						NL80211_CHAN_NO_HT)
			config_bands = BAND_A;
		else
			config_bands = BAND_AN | BAND_A;
	}

	if (!((config_bands | adapter->fw_bands) & ~adapter->fw_bands)) {
		adapter->config_bands = config_bands;
		adapter->adhoc_start_band = config_bands;

		if ((config_bands & BAND_GN) || (config_bands & BAND_AN))
			adapter->adhoc_11n_enabled = true;
		else
			adapter->adhoc_11n_enabled = false;
	}

	adapter->sec_chan_offset =
		mwifiex_chan_type_to_sec_chan_offset(
			cfg80211_get_chandef_type(&params->chandef));
	priv->adhoc_channel = ieee80211_frequency_to_channel(
				params->chandef.chan->center_freq);

	mwifiex_dbg(adapter, INFO,
		    "info: set ibss band %d, chan %d, chan offset %d\n",
		    config_bands, priv->adhoc_channel,
		    adapter->sec_chan_offset);

	return 0;
}
