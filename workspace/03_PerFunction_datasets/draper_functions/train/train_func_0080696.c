be_db_close( void )
{
	BackendDB *be;

	LDAP_STAILQ_FOREACH( be, &backendDB, be_next ) {
		if ( be->bd_info->bi_db_close ) {
			be->bd_info->bi_db_close( be, NULL );
		}
	}

	if ( frontendDB->bd_info->bi_db_close ) {
		frontendDB->bd_info->bi_db_close( frontendDB, NULL );
	}

}
