read_auth(struct east_state *es, struct ieee80211_frame *wh, int len)
{
	unsigned short *sp = (unsigned short*) (wh+1);

	if (len) {}

	if (es->es_state != S_SENDAUTH)
		return;

	if (!for_me_and_from_ap(es, wh))
		return;

	if (le16toh(*sp) != 0) {
		printf("weird auth algo: %d\n", le16toh(*sp));
		return;
	}

	sp++;
	if (le16toh(*sp) != 2) {
		printf("weird auth transno: %d\n", le16toh(*sp));
		return;
	}

	sp++;
	if (le16toh(*sp) != 0) {
		printf("Auth unsuccesful %d\n", le16toh(*sp));
		exit(1);
	}

	printf("Authenticated\n");
	es->es_state = S_SENDASSOC;
}
