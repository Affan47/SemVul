oc_find_name( const char *name_or_oid )
{
	struct objclass	*oc;
	char			*ocname = NULL;

	oc_lock_read();
	if ( NULL != ( oc = oc_find_nolock( name_or_oid, NULL, PR_FALSE ))) {
		ocname = slapi_ch_strdup( oc->oc_name );
	}
	oc_unlock();

	return ocname;
}
