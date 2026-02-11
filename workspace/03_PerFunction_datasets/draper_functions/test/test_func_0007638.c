srp_rsp ( struct srp_device *srpdev,
		     const void *data, size_t len ) {
	const struct srp_rsp *rsp = data;
	struct srp_command *srpcmd;
	struct scsi_rsp response;
	const void *sense;
	ssize_t data_out_residual_count;
	ssize_t data_in_residual_count;


	if ( len < sizeof ( *rsp ) ) {
		DBGC ( srpdev, "SRP %p RSP too short (%zd bytes)\n",
		       srpdev, len );
		return -EINVAL;
	}
	DBGC2 ( srpdev, "SRP %p tag %08x RSP stat %02x dores %08x dires "
		"%08x valid %02x%s%s%s%s%s%s\n",
		srpdev, ntohl ( rsp->tag.dwords[1] ), rsp->status,
		ntohl ( rsp->data_out_residual_count ),
		ntohl ( rsp->data_in_residual_count ), rsp->valid,
		( ( rsp->valid & SRP_RSP_VALID_DIUNDER ) ? " diunder" : "" ),
		( ( rsp->valid & SRP_RSP_VALID_DIOVER ) ? " diover" : "" ),
		( ( rsp->valid & SRP_RSP_VALID_DOUNDER ) ? " dounder" : "" ),
		( ( rsp->valid & SRP_RSP_VALID_DOOVER ) ? " doover" : "" ),
		( ( rsp->valid & SRP_RSP_VALID_SNSVALID ) ? " sns" : "" ),
		( ( rsp->valid & SRP_RSP_VALID_RSPVALID ) ? " rsp" : "" ) );


	srpcmd = srp_find_tag ( srpdev, ntohl ( rsp->tag.dwords[1] ) );
	if ( ! srpcmd ) {
		DBGC ( srpdev, "SRP %p tag %08x unrecognised RSP\n",
		       srpdev, ntohl ( rsp->tag.dwords[1] ) );
		return -ENOENT;
	}


	srpcmd_get ( srpcmd );


	memset ( &response, 0, sizeof ( response ) );
	response.status = rsp->status;
	data_out_residual_count = ntohl ( rsp->data_out_residual_count );
	data_in_residual_count = ntohl ( rsp->data_in_residual_count );
	if ( rsp->valid & SRP_RSP_VALID_DOOVER ) {
		response.overrun = data_out_residual_count;
	} else if ( rsp->valid & SRP_RSP_VALID_DOUNDER ) {
		response.overrun = -(data_out_residual_count);
	} else if ( rsp->valid & SRP_RSP_VALID_DIOVER ) {
		response.overrun = data_in_residual_count;
	} else if ( rsp->valid & SRP_RSP_VALID_DIUNDER ) {
		response.overrun = -(data_in_residual_count);
	}
	sense = srp_rsp_sense_data ( rsp );
	if ( sense )
		memcpy ( &response.sense, sense, sizeof ( response.sense ) );


	scsi_response ( &srpcmd->scsi, &response );


	srpcmd_close ( srpcmd, 0 );


	srpcmd_put ( srpcmd );

	return 0;
}
