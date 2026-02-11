ipw_add_scan_channels(struct ipw_priv *priv,
				  struct ipw_scan_request_ext *scan,
				  int scan_type)
{
	int channel_index = 0;
	const struct libipw_geo *geo;
	int i;

	geo = libipw_get_geo(priv->ieee);

	if (priv->ieee->freq_band & LIBIPW_52GHZ_BAND) {
		int start = channel_index;
		for (i = 0; i < geo->a_channels; i++) {
			if ((priv->status & STATUS_ASSOCIATED) &&
			    geo->a[i].channel == priv->channel)
				continue;
			channel_index++;
			scan->channels_list[channel_index] = geo->a[i].channel;
			ipw_set_scan_type(scan, channel_index,
					  geo->a[i].
					  flags & LIBIPW_CH_PASSIVE_ONLY ?
					  IPW_SCAN_PASSIVE_FULL_DWELL_SCAN :
					  scan_type);
		}

		if (start != channel_index) {
			scan->channels_list[start] = (u8) (IPW_A_MODE << 6) |
			    (channel_index - start);
			channel_index++;
		}
	}

	if (priv->ieee->freq_band & LIBIPW_24GHZ_BAND) {
		int start = channel_index;
		if (priv->config & CFG_SPEED_SCAN) {
			int index;
			u8 channels[LIBIPW_24GHZ_CHANNELS] = {

				[0] = 0
			};

			u8 channel;
			while (channel_index < IPW_SCAN_CHANNELS - 1) {
				channel =
				    priv->speed_scan[priv->speed_scan_pos];
				if (channel == 0) {
					priv->speed_scan_pos = 0;
					channel = priv->speed_scan[0];
				}
				if ((priv->status & STATUS_ASSOCIATED) &&
				    channel == priv->channel) {
					priv->speed_scan_pos++;
					continue;
				}


				if (channels[channel - 1] != 0)
					break;

				channels[channel - 1] = 1;
				priv->speed_scan_pos++;
				channel_index++;
				scan->channels_list[channel_index] = channel;
				index =
				    libipw_channel_to_index(priv->ieee, channel);
				ipw_set_scan_type(scan, channel_index,
						  geo->bg[index].
						  flags &
						  LIBIPW_CH_PASSIVE_ONLY ?
						  IPW_SCAN_PASSIVE_FULL_DWELL_SCAN
						  : scan_type);
			}
		} else {
			for (i = 0; i < geo->bg_channels; i++) {
				if ((priv->status & STATUS_ASSOCIATED) &&
				    geo->bg[i].channel == priv->channel)
					continue;
				channel_index++;
				scan->channels_list[channel_index] =
				    geo->bg[i].channel;
				ipw_set_scan_type(scan, channel_index,
						  geo->bg[i].
						  flags &
						  LIBIPW_CH_PASSIVE_ONLY ?
						  IPW_SCAN_PASSIVE_FULL_DWELL_SCAN
						  : scan_type);
			}
		}

		if (start != channel_index) {
			scan->channels_list[start] = (u8) (IPW_B_MODE << 6) |
			    (channel_index - start);
		}
	}
}
