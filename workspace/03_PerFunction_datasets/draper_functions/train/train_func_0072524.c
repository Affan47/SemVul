network_add(struct ieee80211_frame *wh)
{
	struct network *n;
	unsigned char *bssid = get_bssid(wh);

	if (!bssid)
		return NULL;

	n = network_new();

	memcpy(n->n_bssid, bssid, sizeof(n->n_bssid));

	do_network_add(n);

	return n;
}
