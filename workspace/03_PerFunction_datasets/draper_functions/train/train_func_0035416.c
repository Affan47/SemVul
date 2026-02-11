config_build_modules( ConfigArgs *c, CfEntryInfo *ceparent,
	Operation *op, SlapReply *rs )
{
	int i;
	ModPaths *mp;

	for (i=0, mp=&modpaths; mp; mp=mp->mp_next, i++) {
		if ( BER_BVISNULL( &mp->mp_path ) && !mp->mp_loads )
			continue;
		c->value_dn.bv_val = c->log;
		c->value_dn.bv_len = snprintf(c->value_dn.bv_val, sizeof( c->log ), "cn=module" SLAP_X_ORDERED_FMT, i);
		if ( c->value_dn.bv_len >= sizeof( c->log ) ) {

			return -1;
		}
		c->ca_private = mp;
		if ( ! config_build_entry( op, rs, ceparent, c, &c->value_dn, &CFOC_MODULE, NULL )) {
			return -1;
		}
	}
        return 0;
}
