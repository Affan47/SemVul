ath9k_update_p2p_ps_timer(struct ath_softc *sc, struct ath_vif *avp)
{
	struct ath_hw *ah = sc->sc_ah;
	s32 tsf, target_tsf;

	if (!avp || !avp->noa.has_next_tsf)
		return;

	ath9k_hw_gen_timer_stop(ah, sc->p2p_ps_timer);

	tsf = ath9k_hw_gettsf32(sc->sc_ah);

	target_tsf = avp->noa.next_tsf;
	if (!avp->noa.absent)
		target_tsf -= ATH_P2P_PS_STOP_TIME;

	if (target_tsf - tsf < ATH_P2P_PS_STOP_TIME)
		target_tsf = tsf + ATH_P2P_PS_STOP_TIME;

	ath9k_hw_gen_timer_start(ah, sc->p2p_ps_timer, (u32) target_tsf, 1000000);
}
