qib7322_ahb_read ( struct qib7322 *qib7322, unsigned int location,
			      uint32_t *data ) {
	struct QIB_7322_ahb_transaction_reg xact;
	int rc;


	*data = 0;


	memset ( &xact, 0, sizeof ( xact ) );
	BIT_FILL_2 ( &xact,
		     ahb_address, QIB7322_AHB_LOC_ADDRESS ( location ),
		     write_not_read, 0 );
	qib7322_writeq ( qib7322, &xact, QIB_7322_ahb_transaction_reg_offset );


	if ( ( rc = qib7322_ahb_wait ( qib7322 ) ) != 0 )
		return rc;


	qib7322_readq ( qib7322, &xact, QIB_7322_ahb_transaction_reg_offset );
	*data = BIT_GET ( &xact, ahb_data );
	return 0;
}
