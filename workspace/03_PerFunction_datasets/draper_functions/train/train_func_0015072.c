ath_chanctx_set_next(struct ath_softc *sc, bool force)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_chanctx *old_ctx;
	struct timespec ts;
	bool measure_time = false;
	bool send_ps = false;
	bool queues_stopped = false;

	spin_lock_bh(&sc->chan_lock);
	if (!sc->next_chan) {
		spin_unlock_bh(&sc->chan_lock);
		return;
	}

	if (!force && ath_chanctx_defer_switch(sc)) {
		spin_unlock_bh(&sc->chan_lock);
		return;
	}

	ath_dbg(common, CHAN_CTX,
		"%s: current: %d MHz, next: %d MHz\n",
		__func__,
		sc->cur_chan->chandef.center_freq1,
		sc->next_chan->chandef.center_freq1);

	if (sc->cur_chan != sc->next_chan) {
		ath_dbg(common, CHAN_CTX,
			"Stopping current chanctx: %d\n",
			sc->cur_chan->chandef.center_freq1);
		sc->cur_chan->stopped = true;
		spin_unlock_bh(&sc->chan_lock);

		if (sc->next_chan == &sc->offchannel.chan) {
			getrawmonotonic(&ts);
			measure_time = true;
		}

		ath9k_chanctx_stop_queues(sc, sc->cur_chan);
		queues_stopped = true;

		__ath9k_flush(sc->hw, ~0, true, false, false);

		if (ath_chanctx_send_ps_frame(sc, true))
			__ath9k_flush(sc->hw, BIT(IEEE80211_AC_VO),
				      false, false, false);

		send_ps = true;
		spin_lock_bh(&sc->chan_lock);

		if (sc->cur_chan != &sc->offchannel.chan) {
			getrawmonotonic(&sc->cur_chan->tsf_ts);
			sc->cur_chan->tsf_val = ath9k_hw_gettsf64(sc->sc_ah);
		}
	}
	old_ctx = sc->cur_chan;
	sc->cur_chan = sc->next_chan;
	sc->cur_chan->stopped = false;
	sc->next_chan = NULL;

	if (!sc->sched.offchannel_pending)
		sc->sched.offchannel_duration = 0;

	if (sc->sched.state != ATH_CHANCTX_STATE_FORCE_ACTIVE)
		sc->sched.state = ATH_CHANCTX_STATE_IDLE;

	spin_unlock_bh(&sc->chan_lock);

	if (sc->sc_ah->chip_fullsleep ||
	    memcmp(&sc->cur_chandef, &sc->cur_chan->chandef,
		   sizeof(sc->cur_chandef))) {
		ath_dbg(common, CHAN_CTX,
			"%s: Set channel %d MHz\n",
			__func__, sc->cur_chan->chandef.center_freq1);
		ath_set_channel(sc);
		if (measure_time)
			sc->sched.channel_switch_time =
				ath9k_hw_get_tsf_offset(&ts, NULL);


		goto out;
	}

	if (queues_stopped)
		ath9k_chanctx_wake_queues(sc, old_ctx);
out:
	if (send_ps)
		ath_chanctx_send_ps_frame(sc, false);

	ath_offchannel_channel_change(sc);
	ath_chanctx_event(sc, NULL, ATH_CHANCTX_EVENT_SWITCH);
}
