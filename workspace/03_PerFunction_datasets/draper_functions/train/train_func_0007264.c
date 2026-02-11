ath9k_beacon_assign_slot(struct ath_softc *sc, struct ieee80211_vif *vif)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_vif *avp = (void *)vif->drv_priv;
	int slot;

	avp->av_bcbuf = list_first_entry(&sc->beacon.bbuf, struct ath_buf, list);
	list_del(&avp->av_bcbuf->list);

	for (slot = 0; slot < ATH_BCBUF; slot++) {
		if (sc->beacon.bslot[slot] == NULL) {
			avp->av_bslot = slot;
			break;
		}
	}

	sc->beacon.bslot[avp->av_bslot] = vif;
	sc->nbcnvifs++;

	ath_dbg(common, CONFIG, "Added interface at beacon slot: %d\n",
		avp->av_bslot);
}
