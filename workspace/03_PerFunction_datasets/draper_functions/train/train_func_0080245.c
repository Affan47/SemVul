fix_keyblock( KBNODE keyblock )
{
    KBNODE node, last, subkey;
    int fixed=0;


    for( subkey=last=NULL, node = keyblock; node;
					    last=node, node = node->next ) {
	switch( node->pkt->pkttype ) {
	  case PKT_PUBLIC_SUBKEY:
	  case PKT_SECRET_SUBKEY:
	    if( !subkey )
		subkey = last;
	    break;
	  case PKT_SIGNATURE:
	    if( subkey ) {
		PKT_signature *sig = node->pkt->pkt.signature;
		if( sig->sig_class >= 0x10 && sig->sig_class <= 0x13 ) {
		    log_info(_(
			"moving a key signature to the correct place\n"));
		    last->next = node->next;
		    node->next = subkey->next;
		    subkey->next = node;
		    node = last;
		    fixed=1;
		}
	    }
	    break;
	  default: break;
	}
    }

    return fixed;
}
