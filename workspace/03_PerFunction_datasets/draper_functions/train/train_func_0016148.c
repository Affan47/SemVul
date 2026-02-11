show_revocation_reason( PKT_public_key *pk, int mode )
{


    KBNODE node, keyblock = NULL;
    byte fingerprint[MAX_FINGERPRINT_LEN];
    size_t fingerlen;
    int rc;


    fingerprint_from_pk( pk, fingerprint, &fingerlen );
    rc = get_keyblock_byfprint( &keyblock, fingerprint, fingerlen );
    if( rc ) {
	log_debug( "failed to get the keyblock\n");
	return;
    }

    for( node=keyblock; node; node = node->next ) {
        if( (mode && node->pkt->pkttype == PKT_PUBLIC_KEY) ||
	  ( ( node->pkt->pkttype == PKT_PUBLIC_KEY
	      || node->pkt->pkttype == PKT_PUBLIC_SUBKEY )
	    && !cmp_public_keys( node->pkt->pkt.public_key, pk ) ) )
	    break;
    }
    if( !node ) {
	log_debug("Oops, PK not in keyblock\n");
	release_kbnode( keyblock );
	return;
    }

    for( node = node->next; node ; node = node->next ) {
	if( node->pkt->pkttype == PKT_PUBLIC_SUBKEY )
	    break;
	if( node->pkt->pkttype == PKT_SIGNATURE
	    && (node->pkt->pkt.signature->sig_class == 0x20
		|| node->pkt->pkt.signature->sig_class == 0x28 ) ) {

		do_show_revocation_reason ( node->pkt->pkt.signature );
		break;
	}
    }


    if(!node && !mode)
      show_revocation_reason(pk,1);

    release_kbnode( keyblock );
}
