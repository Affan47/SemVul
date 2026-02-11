b43_op_config(struct ieee80211_hw *hw, u32 changed)
{
	struct b43_wl *wl = hw_to_b43_wl(hw);
	struct b43_wldev *dev = wl->current_dev;
	struct b43_phy *phy = &dev->phy;
	struct ieee80211_conf *conf = &hw->conf;
	int antenna;
	int err = 0;

	mutex_lock(&wl->mutex);
	b43_mac_suspend(dev);

	if (changed & IEEE80211_CONF_CHANGE_LISTEN_INTERVAL)
		b43_set_beacon_listen_interval(dev, conf->listen_interval);

	if (changed & IEEE80211_CONF_CHANGE_CHANNEL) {
		phy->chandef = &conf->chandef;
		phy->channel = conf->chandef.chan->hw_value;


		err = b43_switch_band(dev, conf->chandef.chan);
		if (err)
			goto out_mac_enable;


		b43_switch_channel(dev, phy->channel);
	}

	if (changed & IEEE80211_CONF_CHANGE_RETRY_LIMITS)
		b43_set_retry_limits(dev, conf->short_frame_max_tx_count,
					  conf->long_frame_max_tx_count);
	changed &= ~IEEE80211_CONF_CHANGE_RETRY_LIMITS;
	if (!changed)
		goto out_mac_enable;

	dev->wl->radiotap_enabled = !!(conf->flags & IEEE80211_CONF_MONITOR);


	if (conf->power_level != 0) {
		if (conf->power_level != phy->desired_txpower) {
			phy->desired_txpower = conf->power_level;
			b43_phy_txpower_check(dev, B43_TXPWR_IGNORE_TIME |
						   B43_TXPWR_IGNORE_TSSI);
		}
	}


	antenna = B43_ANTENNA_DEFAULT;
	b43_mgmtframe_txantenna(dev, antenna);
	antenna = B43_ANTENNA_DEFAULT;
	if (phy->ops->set_rx_antenna)
		phy->ops->set_rx_antenna(dev, antenna);

	if (wl->radio_enabled != phy->radio_on) {
		if (wl->radio_enabled) {
			b43_software_rfkill(dev, false);
			b43info(dev->wl, "Radio turned on by software\n");
			if (!dev->radio_hw_enable) {
				b43info(dev->wl, "The hardware RF-kill button "
					"still turns the radio physically off. "
					"Press the button to turn it on.\n");
			}
		} else {
			b43_software_rfkill(dev, true);
			b43info(dev->wl, "Radio turned off by software\n");
		}
	}

out_mac_enable:
	b43_mac_enable(dev);
	mutex_unlock(&wl->mutex);

	return err;
}
