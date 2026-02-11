wifi_read(void)
{
	struct state *s = &_state;
	unsigned char buf[2048];
	int rd;
	struct rx_info ri;
        struct ieee80211_frame* wh = (struct ieee80211_frame*) buf;
	struct network *n;

	rd = wi_read(s->s_wi, buf, sizeof(buf), &ri);
	if (rd <= 0)
		err(1, "wi_read()");

	s->s_ri = &ri;

	n = network_update(wh);

	switch (wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK) {
	case IEEE80211_FC0_TYPE_MGT:
		wifi_mgt(n, wh, rd);
		break;

	case IEEE80211_FC0_TYPE_CTL:
		wifi_ctl(wh, rd);
		break;

	case IEEE80211_FC0_TYPE_DATA:
		wifi_data(n, wh, rd);
		break;

	default:
		printf("Unknown type %d\n", wh->i_fc[0]);
	}
}
