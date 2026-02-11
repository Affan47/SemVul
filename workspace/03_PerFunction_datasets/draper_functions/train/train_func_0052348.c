ath9k_calculate_iter_data(struct ath_softc *sc,
			       struct ath_chanctx *ctx,
			       struct ath9k_vif_iter_data *iter_data)
{
	struct ath_vif *avp;


	memset(iter_data, 0, sizeof(*iter_data));
	eth_broadcast_addr(iter_data->mask);
	iter_data->slottime = ATH9K_SLOT_TIME_9;

	list_for_each_entry(avp, &ctx->vifs, list)
		ath9k_vif_iter(iter_data, avp->vif->addr, avp->vif);

	ath9k_update_bssid_mask(sc, ctx, iter_data);
}
