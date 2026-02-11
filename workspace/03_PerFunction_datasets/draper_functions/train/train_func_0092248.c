qib7322_ahb_mod_reg ( struct qib7322 *qib7322, unsigned int location,
				 uint32_t value, uint32_t mask ) {
	uint32_t old_value;
	uint32_t new_value;
	int rc;

	DBG_DISABLE ( DBGLVL_IO );


	assert ( ( value & mask ) == value );


	if ( ( rc = qib7322_ahb_request ( qib7322, location ) ) != 0 )
		goto out;


	if ( ( rc = qib7322_ahb_read ( qib7322, location, &old_value ) ) != 0 )
		goto out_release;


	new_value = ( ( old_value & ~mask ) | value );
	DBGCP ( qib7322, "QIB7322 %p AHB %x %#08x => %#08x\n",
		qib7322, location, old_value, new_value );
	if ( ( rc = qib7322_ahb_write ( qib7322, location, new_value ) ) != 0 )
		goto out_release;

 out_release:

	qib7322_ahb_release ( qib7322 );
 out:
	DBG_ENABLE ( DBGLVL_IO );
	return rc;
}
