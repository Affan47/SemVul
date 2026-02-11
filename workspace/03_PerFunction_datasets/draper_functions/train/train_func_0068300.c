il4965_rs_alloc_sta(void *il_rate, struct ieee80211_sta *sta, gfp_t gfp)
{
	struct il_station_priv *sta_priv =
	    (struct il_station_priv *)sta->drv_priv;
	struct il_priv *il;

	il = (struct il_priv *)il_rate;
	D_RATE("create station rate scale win\n");

	return &sta_priv->lq_sta;
}
