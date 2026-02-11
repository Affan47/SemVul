rtl818x_config(struct net80211_device *dev, int changed)
{
	struct rtl818x_priv *priv = dev->priv;
	int i;

	if (changed & NET80211_CFG_CHANNEL)
		priv->rf->set_chan(dev, &dev->channels[dev->channel]);

	if (changed & NET80211_CFG_ASSOC) {
		for (i = 0; i < ETH_ALEN; i++)
			rtl818x_iowrite8(priv, &priv->map->BSSID[i], dev->bssid[i]);
		rtl818x_iowrite8(priv, &priv->map->MSR,
				 dev->state & NET80211_ASSOCIATED?
					RTL818X_MSR_INFRA : RTL818X_MSR_NO_LINK);
	}

	if (changed & NET80211_CFG_PHY_PARAMS)
		priv->rf->conf_erp(dev);

	if (changed & NET80211_CFG_RATE) {


		int hw_rate;
		for (hw_rate = 0; hw_rate < RTL818X_NR_RATES &&
			     rtl818x_rates[hw_rate] != dev->rates[dev->rate];
		     hw_rate++)
			;
		if (hw_rate >= RTL818X_NR_RATES)
			return -EINVAL;

		priv->hw_rate = hw_rate;


		for (hw_rate = 0; hw_rate < RTL818X_NR_RATES &&
			     rtl818x_rates[hw_rate] !=
				dev->rates[dev->rtscts_rate];
		     hw_rate++)
			;
		if (hw_rate >= RTL818X_NR_RATES)
			hw_rate = priv->hw_rate;

		priv->hw_rtscts_rate = hw_rate;
	}

	return 0;
}
