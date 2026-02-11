proc_ctl(struct wstate *ws, int stype)
{
	if (stype == IEEE80211_FC0_SUBTYPE_ACK) {
		ws->ws_waiting_ack = 0;
		return;

	} else if (stype == IEEE80211_FC0_SUBTYPE_RTS) {
		return;

	} else if (stype == IEEE80211_FC0_SUBTYPE_CTS) {
		return;
	}

	time_print ("got CTL=%x\n", stype);
}
