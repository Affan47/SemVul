mwifiex_dfs_cac_work_queue(struct work_struct *work)
{
	struct cfg80211_chan_def chandef;
	struct delayed_work *delayed_work =
			container_of(work, struct delayed_work, work);
	struct mwifiex_private *priv =
			container_of(delayed_work, struct mwifiex_private,
				     dfs_cac_work);

	if (WARN_ON(!priv))
		return;

	chandef = priv->dfs_chandef;
	if (priv->wdev.cac_started) {
		mwifiex_dbg(priv->adapter, MSG,
			    "CAC timer finished; No radar detected\n");
		cfg80211_cac_event(priv->netdev, &chandef,
				   NL80211_RADAR_CAC_FINISHED,
				   GFP_KERNEL);
	}
}
