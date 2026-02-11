smbk5pwd_db_init(BackendDB *be, ConfigReply *cr)
{
	slap_overinst	*on = (slap_overinst *)be->bd_info;
	smbk5pwd_t	*pi;

	pi = ch_calloc( 1, sizeof( smbk5pwd_t ) );
	if ( pi == NULL ) {
		return 1;
	}
	on->on_bi.bi_private = (void *)pi;

	return 0;
}
