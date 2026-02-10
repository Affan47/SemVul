linda_ib_epb_wait ( struct linda *linda,
			    struct QIB_7220_ibsd_epb_transaction_reg *xact ) {
	unsigned int i;


	linda_readq ( linda, xact, QIB_7220_ibsd_epb_transaction_reg_offset );

	for ( i = 0 ; i < LINDA_EPB_XACT_MAX_WAIT_US ; i++ ) {
		linda_readq ( linda, xact,
			      QIB_7220_ibsd_epb_transaction_reg_offset );
		if ( BIT_GET ( xact, ib_epb_rdy ) ) {
			if ( BIT_GET ( xact, ib_epb_req_error ) ) {
				DBGC ( linda, "Linda %p EPB transaction "
				       "failed\n", linda );
				return -EIO;
			} else {
				return 0;
			}
		}
		udelay ( 1 );
	}

	DBGC ( linda, "Linda %p timed out waiting for IB EPB transaction\n",
	       linda );
	return -ETIMEDOUT;
}
