process_packet(void *packet, int len)
{
        struct ieee80211_frame *wh = (struct ieee80211_frame*) packet;

#if 0
	printf("GOT %d\n", len);
	hexdump(packet, len);
#endif

	if (len < (int) sizeof(*wh))
		return;

	switch (wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK) {
	case IEEE80211_FC0_TYPE_MGT:
		switch (wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) {
		case IEEE80211_FC0_SUBTYPE_BEACON:
			process_beacon(wh, len);
			break;

		case IEEE80211_FC0_SUBTYPE_ASSOC_REQ:
			grab_hidden_ssid(wh->i_addr1, wh, len, 2 + 2);
			break;

		case IEEE80211_FC0_SUBTYPE_REASSOC_REQ:
			grab_hidden_ssid(wh->i_addr1, wh, len, 2 + 2 + 6);
			break;

		case IEEE80211_FC0_SUBTYPE_PROBE_RESP:
			grab_hidden_ssid(wh->i_addr2, wh, len, 8 + 2 + 2);
			break;
		}
		break;

        case IEEE80211_FC0_TYPE_DATA:
		process_data(wh, len);
		break;
	}
}
