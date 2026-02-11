ibft_fill_initiator ( struct ibft_initiator *initiator,
				 struct ibft_string_block *strings ) {
	const char *initiator_iqn = iscsi_initiator_iqn();
	int rc;

	if ( ( rc = ibft_set_string ( strings, &initiator->initiator_name,
				      initiator_iqn ) ) != 0 )
		return rc;
	DBG ( "iBFT initiator hostname = %s\n",
	      ibft_string ( strings, &initiator->initiator_name ) );

	return 0;
}
