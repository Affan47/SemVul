windows_private_set_raw_entry(const Repl_Agmt *ra, Slapi_Entry *e)
{
	Dirsync_Private *dp;

	LDAPDebug0Args( LDAP_DEBUG_TRACE, "=> windows_private_set_raw_entry\n" );

	dp = (Dirsync_Private *) agmt_get_priv(ra);
	PR_ASSERT (dp);


	if (windows_private_get_keep_raw_entry(ra)) {
		slapi_entry_free(e);
	} else {
		slapi_entry_free(dp->raw_entry);
		dp->raw_entry = e;
	}

	LDAPDebug0Args( LDAP_DEBUG_TRACE, "<= windows_private_set_raw_entry\n" );
}
