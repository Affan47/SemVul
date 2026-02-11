wpa_start ( struct net80211_device *dev, struct wpa_common_ctx *ctx,
		const void *pmk, size_t pmk_len )
{
	struct io_buffer *iob;
	struct ieee80211_frame *hdr;
	struct ieee80211_beacon *beacon;
	u8 *ap_rsn_ie = NULL, *ap_rsn_ie_end;

	if ( ! dev->rsn_ie || ! dev->associating )
		return -EINVAL;

	ctx->dev = dev;
	memcpy ( ctx->pmk, pmk, ctx->pmk_len = pmk_len );
	ctx->state = WPA_READY;
	ctx->replay = ~0ULL;

	iob = dev->associating->beacon;
	hdr = iob->data;
	beacon = ( struct ieee80211_beacon * ) hdr->data;
	ap_rsn_ie = sec80211_find_rsn ( beacon->info_element, iob->tail,
					&ctx->ap_rsn_is_rsn, &ap_rsn_ie_end );
	if ( ap_rsn_ie ) {
		ctx->ap_rsn_ie = malloc ( ap_rsn_ie_end - ap_rsn_ie );
		if ( ! ctx->ap_rsn_ie )
			return -ENOMEM;
		memcpy ( ctx->ap_rsn_ie, ap_rsn_ie, ap_rsn_ie_end - ap_rsn_ie );
		ctx->ap_rsn_ie_len = ap_rsn_ie_end - ap_rsn_ie;
	} else {
		return -ENOENT;
	}

	ctx->crypt = dev->associating->crypto;
	ctx->gcrypt = NET80211_CRYPT_UNKNOWN;

	list_add_tail ( &ctx->list, &wpa_contexts );
	return 0;
}
