undinet_transmit ( struct net_device *netdev,
			      struct io_buffer *iobuf ) {
	struct s_PXENV_UNDI_TRANSMIT undi_transmit;
	size_t len = iob_len ( iobuf );
	int rc;


	if ( len > sizeof ( basemem_packet ) )
		len = sizeof ( basemem_packet );
	memcpy ( &basemem_packet, iobuf->data, len );


	memset ( &undi_transmit, 0, sizeof ( undi_transmit ) );
	undi_transmit.DestAddr.segment = rm_ds;
	undi_transmit.DestAddr.offset = __from_data16 ( &undinet_tbd );
	undi_transmit.TBD.segment = rm_ds;
	undi_transmit.TBD.offset = __from_data16 ( &undinet_tbd );


	undinet_tbd.ImmedLength = len;
	undinet_tbd.Xmit.segment = rm_ds;
	undinet_tbd.Xmit.offset = __from_data16 ( basemem_packet );


	if ( ( rc = pxeparent_call ( undinet_entry, PXENV_UNDI_TRANSMIT,
				     &undi_transmit,
				     sizeof ( undi_transmit ) ) ) != 0 )
		goto done;


	netdev_tx_complete ( netdev, iobuf );

 done:
	return rc;
}
