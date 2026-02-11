isapnp_find_logdevid ( unsigned int logdev,
				  struct isapnp_logdevid *logdevid ) {
	unsigned int i;
	int rc;

	for ( i = 0 ; i <= logdev ; i++ ) {
		if ( ( rc = isapnp_find_tag ( ISAPNP_TAG_LOGDEVID, logdevid,
					      sizeof ( *logdevid ) ) ) != 0 )
			return rc;
	}
	return 0;
}
