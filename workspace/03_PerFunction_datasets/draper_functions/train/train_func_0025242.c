ath9k_remove_chanctx(struct ieee80211_hw *hw,
				 struct ieee80211_chanctx_conf *conf)
{
	struct ath_softc *sc = hw->priv;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_chanctx *ctx = ath_chanctx_get(conf);

	mutex_lock(&sc->mutex);

	ath_dbg(common, CHAN_CTX,
		"Remove channel context: %d MHz\n",
		conf->def.chan->center_freq);

	ctx->assigned = false;
	ctx->hw_queue_base = 0;
	ath_chanctx_event(sc, NULL, ATH_CHANCTX_EVENT_UNASSIGN);

	mutex_unlock(&sc->mutex);
}
