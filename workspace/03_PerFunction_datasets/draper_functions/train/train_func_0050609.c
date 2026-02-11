rtl8225_rf_set_channel(struct ieee80211_hw *dev,
				   struct ieee80211_conf *conf)
{
	struct rtl8187_priv *priv = dev->priv;
	int chan =
		ieee80211_frequency_to_channel(conf->chandef.chan->center_freq);

	if (priv->rf->init == rtl8225_rf_init)
		rtl8225_rf_set_tx_power(dev, chan);
	else if (priv->rf->init == rtl8225z2_rf_init)
		rtl8225z2_rf_set_tx_power(dev, chan);
	else
		rtl8225z2_b_rf_set_tx_power(dev, chan);

	rtl8225_write(dev, 0x7, rtl8225_chan[chan - 1]);
	msleep(10);
}
