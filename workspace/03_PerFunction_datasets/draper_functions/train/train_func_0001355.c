iwl_dealloc_bcast_stations(struct iwl_priv *priv)
{
	int i;

	spin_lock_bh(&priv->sta_lock);
	for (i = 0; i < IWLAGN_STATION_COUNT; i++) {
		if (!(priv->stations[i].used & IWL_STA_BCAST))
			continue;

		priv->stations[i].used &= ~IWL_STA_UCODE_ACTIVE;
		priv->num_stations--;
		if (WARN_ON(priv->num_stations < 0))
			priv->num_stations = 0;
		kfree(priv->stations[i].lq);
		priv->stations[i].lq = NULL;
	}
	spin_unlock_bh(&priv->sta_lock);
}
