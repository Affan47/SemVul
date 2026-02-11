wpa_send_eapol ( struct io_buffer *iob, struct wpa_common_ctx *ctx,
			    struct wpa_kie *kie )
{
	struct eapol_key_pkt *pkt = iob->data;
	struct eapol_frame *eapol = iob_push ( iob, EAPOL_HDR_LEN );

	pkt->info = htons ( pkt->info );
	pkt->keysize = htons ( pkt->keysize );
	pkt->datalen = htons ( pkt->datalen );
	pkt->replay = cpu_to_be64 ( pkt->replay );
	eapol->version = EAPOL_THIS_VERSION;
	eapol->type = EAPOL_TYPE_KEY;
	eapol->length = htons ( iob->tail - iob->data - sizeof ( *eapol ) );

	memset ( pkt->mic, 0, sizeof ( pkt->mic ) );
	if ( kie )
		kie->mic ( &ctx->ptk.kck, eapol, EAPOL_HDR_LEN +
			   sizeof ( *pkt ) + ntohs ( pkt->datalen ),
			   pkt->mic );

	return net_tx ( iob, ctx->dev->netdev, &eapol_protocol,
			ctx->dev->bssid, ctx->dev->netdev->ll_addr );
}
