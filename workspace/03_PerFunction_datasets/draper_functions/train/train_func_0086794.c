parse_mdc( IOBUF inp, int pkttype, unsigned long pktlen,
				   PACKET *pkt, int new_ctb )
{
    int rc = 0;
    PKT_mdc *mdc;
    byte *p;

    mdc = pkt->pkt.mdc=  xmalloc(sizeof *pkt->pkt.mdc );
    if( list_mode )
	fprintf (listfp, ":mdc packet: length=%lu\n", pktlen);
    if( !new_ctb || pktlen != 20 ) {
	log_error("mdc_packet with invalid encoding\n");
        rc = G10ERR_INVALID_PACKET;
	goto leave;
    }
    p = mdc->hash;
    for( ; pktlen; pktlen--, p++ )
	*p = iobuf_get_noeof(inp);

  leave:
    return rc;
}
