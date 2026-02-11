ath_rx_ps(struct ath_softc *sc, struct sk_buff *skb, bool mybeacon)
{
	struct ieee80211_hdr *hdr;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);

	hdr = (struct ieee80211_hdr *)skb->data;


	if (((sc->ps_flags & PS_WAIT_FOR_BEACON) || ath9k_check_auto_sleep(sc))
	    && mybeacon) {
		ath_rx_ps_beacon(sc, skb);
	} else if ((sc->ps_flags & PS_WAIT_FOR_CAB) &&
		   (ieee80211_is_data(hdr->frame_control) ||
		    ieee80211_is_action(hdr->frame_control)) &&
		   is_multicast_ether_addr(hdr->addr1) &&
		   !ieee80211_has_moredata(hdr->frame_control)) {


		sc->ps_flags &= ~(PS_WAIT_FOR_CAB | PS_WAIT_FOR_BEACON);
		ath_dbg(common, PS,
			"All PS CAB frames received, back to sleep\n");
	} else if ((sc->ps_flags & PS_WAIT_FOR_PSPOLL_DATA) &&
		   !is_multicast_ether_addr(hdr->addr1) &&
		   !ieee80211_has_morefrags(hdr->frame_control)) {
		sc->ps_flags &= ~PS_WAIT_FOR_PSPOLL_DATA;
		ath_dbg(common, PS,
			"Going back to sleep after having received PS-Poll data (0x%lx)\n",
			sc->ps_flags & (PS_WAIT_FOR_BEACON |
					PS_WAIT_FOR_CAB |
					PS_WAIT_FOR_PSPOLL_DATA |
					PS_WAIT_FOR_TX_ACK));
	}
}
