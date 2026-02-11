translucent_ldadd( CfEntryInfo *cei, Entry *e, ConfigArgs *ca )
{
	slap_overinst *on;
	translucent_info *ov;

	Debug(LDAP_DEBUG_TRACE, "==> translucent_ldadd\n", 0, 0, 0);

	if ( cei->ce_type != Cft_Overlay || !cei->ce_bi ||
	     cei->ce_bi->bi_cf_ocs != translucentocs )
		return LDAP_CONSTRAINT_VIOLATION;

	on = (slap_overinst *)cei->ce_bi;
	ov = on->on_bi.bi_private;
	ca->be = &ov->db;
	ca->ca_private = on;
	if ( CONFIG_ONLINE_ADD( ca ))
		ca->cleanup = translucent_ldadd_cleanup;
	else
		ov->defer_db_open = 0;

	return LDAP_SUCCESS;
}
