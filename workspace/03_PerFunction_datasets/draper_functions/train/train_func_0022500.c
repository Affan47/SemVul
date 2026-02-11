linda_ib_epb_request ( struct linda *linda ) {
	struct QIB_7220_ibsd_epb_access_ctrl access;
	unsigned int i;


	memset ( &access, 0, sizeof ( access ) );
	BIT_FILL_1 ( &access, sw_ib_epb_req, 1 );
	linda_writeq ( linda, &access, QIB_7220_ibsd_epb_access_ctrl_offset );


	for ( i = 0 ; i < LINDA_EPB_REQUEST_MAX_WAIT_US ; i++ ) {
		linda_readq ( linda, &access,
			      QIB_7220_ibsd_epb_access_ctrl_offset );
		if ( BIT_GET ( &access, sw_ib_epb_req_granted ) )
			return 0;
		udelay ( 1 );
	}

	DBGC ( linda, "Linda %p timed out waiting for IB EPB request\n",
	       linda );
	return -ETIMEDOUT;
}
