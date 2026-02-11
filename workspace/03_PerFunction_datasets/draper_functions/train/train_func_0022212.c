free_packet( PACKET *pkt )
{
    if( !pkt || !pkt->pkt.generic )
	return;

    if( DBG_MEMORY )
	log_debug("free_packet() type=%d\n", pkt->pkttype );

    switch( pkt->pkttype ) {
      case PKT_SIGNATURE:
	free_seckey_enc( pkt->pkt.signature );
	break;
      case PKT_PUBKEY_ENC:
	free_pubkey_enc( pkt->pkt.pubkey_enc );
	break;
      case PKT_SYMKEY_ENC:
	free_symkey_enc( pkt->pkt.symkey_enc );
	break;
      case PKT_PUBLIC_KEY:
      case PKT_PUBLIC_SUBKEY:
	free_public_key( pkt->pkt.public_key );
	break;
      case PKT_SECRET_KEY:
      case PKT_SECRET_SUBKEY:
	free_secret_key( pkt->pkt.secret_key );
	break;
      case PKT_COMMENT:
	free_comment( pkt->pkt.comment );
	break;
      case PKT_USER_ID:
	free_user_id( pkt->pkt.user_id );
	break;
      case PKT_COMPRESSED:
	free_compressed( pkt->pkt.compressed);
	break;
      case PKT_ENCRYPTED:
      case PKT_ENCRYPTED_MDC:
	free_encrypted( pkt->pkt.encrypted );
	break;
      case PKT_PLAINTEXT:
	free_plaintext( pkt->pkt.plaintext );
	break;
      default:
	xfree( pkt->pkt.generic );
	break;
    }
    pkt->pkt.generic = NULL;
}
