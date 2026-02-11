hermon_setup_mpt ( struct hermon *hermon ) {
	struct hermonprm_mpt mpt;
	uint32_t key;
	int rc;


	key = ( hermon->cap.reserved_mrws | HERMON_MKEY_PREFIX );
	hermon->lkey = ( ( key << 8 ) | ( key >> 24 ) );


	memset ( &mpt, 0, sizeof ( mpt ) );
	MLX_FILL_7 ( &mpt, 0,
		     atomic, 1,
		     rw, 1,
		     rr, 1,
		     lw, 1,
		     lr, 1,
		     pa, 1,
		     r_w, 1 );
	MLX_FILL_1 ( &mpt, 2, mem_key, key );
	MLX_FILL_1 ( &mpt, 3,
		     pd, HERMON_GLOBAL_PD );
	MLX_FILL_1 ( &mpt, 10, len64, 1 );
	if ( ( rc = hermon_cmd_sw2hw_mpt ( hermon,
					   hermon->cap.reserved_mrws,
					   &mpt ) ) != 0 ) {
		DBGC ( hermon, "Hermon %p could not set up MPT: %s\n",
		       hermon, strerror ( rc ) );
		return rc;
	}

	return 0;
}
