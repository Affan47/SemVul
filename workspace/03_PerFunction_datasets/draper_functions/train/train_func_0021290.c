uniqueid2entry(
		backend *be,
		const char *uniqueid,
		back_txn *txn,
		int *err
)
{
#ifdef UUIDCACHE_ON
	ldbm_instance *inst = (ldbm_instance *) be->be_instance_info;
#endif
	struct berval		idv;
	IDList			*idl = NULL;
	struct backentry	*e = NULL;

	LDAPDebug( LDAP_DEBUG_TRACE, "=> uniqueid2entry \"%s\"\n", uniqueid,
		   0, 0 );
#ifdef UUIDCACHE_ON
	e = cache_find_uuid(&inst->inst_cache, uniqueid);
#endif
	if (e == NULL)	{

		PR_ASSERT(uniqueid);
		*err = 0;
		idv.bv_val = (void*)uniqueid;
		idv.bv_len = strlen( idv.bv_val );

		if ( (idl = index_read( be, SLAPI_ATTR_UNIQUEID, indextype_EQUALITY, &idv, txn,
		    err )) == NULL ) {
			if ( *err != 0 && *err != DB_NOTFOUND ) {
				goto ext;
			}
		} else {

			if ( (e = id2entry( be, idl_firstid( idl ), txn, err ))
			    != NULL ) {
				goto ext;
			} else {
				if ( *err != 0 && *err != DB_NOTFOUND ) {
					goto ext;
				}


			}
		}
	} else {
		goto ext;
	}

ext:
	if (NULL != idl) {
		slapi_ch_free( (void**)&idl);
	}

	LDAPDebug( LDAP_DEBUG_TRACE, "<= uniqueid2entry %p\n", e, 0, 0 );
	return( e );
}
