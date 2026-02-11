iwl_set_ht_add_station(struct iwl_priv *priv, u8 index,
				   struct ieee80211_sta *sta,
				   struct iwl_rxon_context *ctx)
{
	__le32 flags, mask;

	iwl_sta_calc_ht_flags(priv, sta, ctx, &flags, &mask);

	lockdep_assert_held(&priv->sta_lock);
	priv->stations[index].sta.station_flags &= ~mask;
	priv->stations[index].sta.station_flags |= flags;
}
