iscsi_rx_data ( struct iscsi_session *iscsi, const void *data,
			   size_t len, size_t remaining ) {
	struct iscsi_bhs_common_response *response
		= &iscsi->rx_bhs.common_response;


	iscsi->cmdsn = ntohl ( response->expcmdsn );
	iscsi->statsn = ntohl ( response->statsn );

	switch ( response->opcode & ISCSI_OPCODE_MASK ) {
	case ISCSI_OPCODE_LOGIN_RESPONSE:
		return iscsi_rx_login_response ( iscsi, data, len, remaining );
	case ISCSI_OPCODE_SCSI_RESPONSE:
		return iscsi_rx_scsi_response ( iscsi, data, len, remaining );
	case ISCSI_OPCODE_DATA_IN:
		return iscsi_rx_data_in ( iscsi, data, len, remaining );
	case ISCSI_OPCODE_R2T:
		return iscsi_rx_r2t ( iscsi, data, len, remaining );
	case ISCSI_OPCODE_NOP_IN:
		return iscsi_rx_nop_in ( iscsi, data, len, remaining );
	default:
		if ( remaining )
			return 0;
		DBGC ( iscsi, "iSCSI %p unknown opcode %02x\n", iscsi,
		       response->opcode );
		return -ENOTSUP_OPCODE;
	}
}
