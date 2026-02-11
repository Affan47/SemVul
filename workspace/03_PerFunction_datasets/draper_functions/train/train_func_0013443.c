hermon_bofm_update ( struct bofm_device *bofm, unsigned int mport,
				const uint8_t *mac ) {
	struct hermon *hermon = container_of ( bofm, struct hermon, bofm );
	struct hermonprm_mod_stat_cfg stat_cfg;
	union {
		uint8_t bytes[8];
		uint32_t dwords[2];
	} buf;
	int rc;


	memset ( &buf, 0, sizeof ( buf ) );
	memcpy ( &buf.bytes[ sizeof ( buf.bytes ) - ETH_ALEN ], mac,
		 ETH_ALEN );


	memset ( &stat_cfg, 0, sizeof ( stat_cfg ) );
	MLX_FILL_2 ( &stat_cfg, 36,
		     mac_m, 1,
		     mac_high, ntohl ( buf.dwords[0] ) );
	MLX_FILL_1 ( &stat_cfg, 37, mac_low, ntohl ( buf.dwords[1] ) );
	if ( ( rc = hermon_mod_stat_cfg ( hermon, mport,
					  HERMON_MOD_STAT_CFG_SET,
					  HERMON_MOD_STAT_CFG_OFFSET ( mac_m ),
					  &stat_cfg ) ) != 0 ) {
		DBGC ( hermon, "Hermon %p port %d could not modify "
		       "configuration: %s\n", hermon, mport, strerror ( rc ) );
		return rc;
	}

	DBGC ( hermon, "Hermon %p port %d updated MAC address to %s\n",
	       hermon, mport, eth_ntoa ( mac ) );

	return 0;
}
