rwm_db_init(
	BackendDB	*be,
	ConfigReply	*cr )
{
	slap_overinst		*on = (slap_overinst *) be->bd_info;
	struct ldaprwmap	*rwmap;
	int			rc = 0;

	rwmap = (struct ldaprwmap *)ch_calloc( 1, sizeof( struct ldaprwmap ) );


	rwmap->rwm_flags = RWM_F_DROP_UNREQUESTED_ATTRS;

	rc = rwm_info_init( &rwmap->rwm_rw );

	on->on_bi.bi_private = (void *)rwmap;

	if ( rc ) {
		(void)rwm_db_destroy( be, NULL );
	}

	return rc;
}
