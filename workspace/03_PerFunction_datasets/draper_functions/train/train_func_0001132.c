rtl8225se_rf_set_channel(struct ieee80211_hw *dev,
				   struct ieee80211_conf *conf)
{
	int chan =
		ieee80211_frequency_to_channel(conf->chandef.chan->center_freq);

	rtl8225sez2_rf_set_tx_power(dev, chan);
	rtl8187se_rf_writereg(dev, 0x7, rtl8225se_chan[chan - 1]);
	if ((rtl8187se_rf_readreg(dev, 0x7) & 0x0F80) !=
		rtl8225se_chan[chan - 1])
		rtl8187se_rf_writereg(dev, 0x7, rtl8225se_chan[chan - 1]);
	usleep_range(10000, 20000);
}
