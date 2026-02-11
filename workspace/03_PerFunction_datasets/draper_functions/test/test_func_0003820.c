ath_chanctx_defer_switch(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);

	if (sc->cur_chan == &sc->offchannel.chan)
		return false;

	switch (sc->sched.state) {
	case ATH_CHANCTX_STATE_SWITCH:
		return false;
	case ATH_CHANCTX_STATE_IDLE:
		if (!sc->cur_chan->switch_after_beacon)
			return false;

		ath_dbg(common, CHAN_CTX,
			"Defer switch, set chanctx state to WAIT_FOR_BEACON\n");

		sc->sched.state = ATH_CHANCTX_STATE_WAIT_FOR_BEACON;
		break;
	default:
		break;
	}

	return true;
}
