add_onepass_sig( CTX c, PACKET *pkt )
{
  KBNODE node;

  if ( c->list )
    add_kbnode( c->list, new_kbnode( pkt ));
  else
    c->list = node = new_kbnode( pkt );

  return 1;
}
