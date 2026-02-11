wpa_install_ptk ( struct wpa_common_ctx *ctx, int len )
{
	DBGC ( ctx, "WPA %p: installing %d-byte pairwise transient key\n",
	       ctx, len );
	DBGC2_HD ( ctx, &ctx->ptk.tk, len );

	return sec80211_install ( &ctx->dev->crypto, ctx->crypt,
				  &ctx->ptk.tk, len, NULL );
}
