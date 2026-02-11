is_armored( const byte *buf )
{
    int ctb, pkttype;

    ctb = *buf;
    if( !(ctb & 0x80) )
	return 1;
    pkttype =  ctb & 0x40 ? (ctb & 0x3f) : ((ctb>>2)&0xf);
    switch( pkttype ) {
      case PKT_MARKER:
      case PKT_SYMKEY_ENC:
      case PKT_ONEPASS_SIG:
      case PKT_PUBLIC_KEY:
      case PKT_SECRET_KEY:
      case PKT_PUBKEY_ENC:
      case PKT_SIGNATURE:
      case PKT_COMMENT:
      case PKT_OLD_COMMENT:
      case PKT_PLAINTEXT:
      case PKT_COMPRESSED:
      case PKT_ENCRYPTED:
	return 0;
    }

    return 1;
}
