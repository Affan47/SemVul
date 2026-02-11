wpa_psk_step ( struct net80211_device *dev )
{
	struct wpa_common_ctx *ctx = dev->handshaker->priv;

	switch ( ctx->state ) {
	case WPA_SUCCESS:
		return 1;
	case WPA_FAILURE:
		return -EACCES;
	default:
		return 0;
	}
}
