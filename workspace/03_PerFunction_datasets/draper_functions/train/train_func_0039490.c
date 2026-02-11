iscsi_socket_deliver ( struct iscsi_session *iscsi,
				  struct io_buffer *iobuf,
				  struct xfer_metadata *meta __unused ) {
	struct iscsi_bhs_common *common = &iscsi->rx_bhs.common;
	int ( * rx ) ( struct iscsi_session *iscsi, const void *data,
		       size_t len, size_t remaining );
	enum iscsi_rx_state next_state;
	size_t frag_len;
	size_t remaining;
	int rc;

	while ( 1 ) {
		switch ( iscsi->rx_state ) {
		case ISCSI_RX_BHS:
			rx = iscsi_rx_bhs;
			iscsi->rx_len = sizeof ( iscsi->rx_bhs );
			next_state = ISCSI_RX_AHS;
			break;
		case ISCSI_RX_AHS:
			rx = iscsi_rx_discard;
			iscsi->rx_len = 4 * ISCSI_AHS_LEN ( common->lengths );
			next_state = ISCSI_RX_DATA;
			break;
		case ISCSI_RX_DATA:
			rx = iscsi_rx_data;
			iscsi->rx_len = ISCSI_DATA_LEN ( common->lengths );
			next_state = ISCSI_RX_DATA_PADDING;
			break;
		case ISCSI_RX_DATA_PADDING:
			rx = iscsi_rx_discard;
			iscsi->rx_len = ISCSI_DATA_PAD_LEN ( common->lengths );
			next_state = ISCSI_RX_BHS;
			break;
		default:
			assert ( 0 );
			rc = -EINVAL;
			goto done;
		}

		frag_len = iscsi->rx_len - iscsi->rx_offset;
		if ( frag_len > iob_len ( iobuf ) )
			frag_len = iob_len ( iobuf );
		remaining = iscsi->rx_len - iscsi->rx_offset - frag_len;
		if ( ( rc = rx ( iscsi, iobuf->data, frag_len,
				 remaining ) ) != 0 ) {
			DBGC ( iscsi, "iSCSI %p could not process received "
			       "data: %s\n", iscsi, strerror ( rc ) );
			goto done;
		}

		iscsi->rx_offset += frag_len;
		iob_pull ( iobuf, frag_len );


		if ( iscsi->rx_offset != iscsi->rx_len ) {
			rc = 0;
			goto done;
		}

		iscsi->rx_state = next_state;
		iscsi->rx_offset = 0;
	}

 done:

	free_iob ( iobuf );


	if ( rc != 0 )
		iscsi_close ( iscsi, rc );

	return rc;
}
