translucent_db_config(
	BackendDB	*be,
	const char	*fname,
	int		lineno,
	int		argc,
	char		**argv
)
{
	slap_overinst *on = (slap_overinst *) be->bd_info;
	translucent_info *ov = on->on_bi.bi_private;

	Debug(LDAP_DEBUG_TRACE, "==> translucent_db_config: %s\n",
	      argc ? argv[0] : "", 0, 0);


	if ( ov->db.bd_info && ov->db.bd_info->bi_db_config )
		return ov->db.bd_info->bi_db_config( &ov->db, fname, lineno,
			argc, argv );
	return SLAP_CONF_UNKNOWN;
}
