attr_syntax_add( struct asyntaxinfo *asip )
{
	int i, rc = LDAP_SUCCESS;
	int nolock = asip->asi_flags & SLAPI_ATTR_FLAG_NOLOCKING;
	struct asyntaxinfo *oldas_from_oid = NULL, *oldas_from_name = NULL;


	if ( NULL != ( oldas_from_oid = attr_syntax_get_by_oid_locking_optional(
					asip->asi_oid, !nolock))) {
		if ( 0 == (asip->asi_flags & SLAPI_ATTR_FLAG_OVERRIDE)) {

			rc = LDAP_TYPE_OR_VALUE_EXISTS;
			goto cleanup_and_return;
		}
	}


	if ( NULL != ( oldas_from_name = attr_syntax_get_by_name_locking_optional(
					asip->asi_name, !nolock))) {
		if ( 0 == (asip->asi_flags & SLAPI_ATTR_FLAG_OVERRIDE)
					|| ( oldas_from_oid != oldas_from_name )) {

			rc = LDAP_TYPE_OR_VALUE_EXISTS;
			goto cleanup_and_return;
		}

		attr_syntax_delete(oldas_from_name);
	} else if ( NULL != oldas_from_oid ) {

		rc = LDAP_TYPE_OR_VALUE_EXISTS;
		goto cleanup_and_return;
	}

	if ( NULL != asip->asi_aliases ) {

		for (i = 0; asip->asi_aliases[i] != NULL; ++i) {
			struct asyntaxinfo	*tmpasi;

			if ( NULL != ( tmpasi =
							attr_syntax_get_by_name_locking_optional(
							asip->asi_aliases[i], !nolock))) {
				if (asip->asi_flags & SLAPI_ATTR_FLAG_OVERRIDE) {


					attr_syntax_delete(tmpasi);
				} else {

					rc = LDAP_TYPE_OR_VALUE_EXISTS;
				}

				attr_syntax_return_locking_optional( tmpasi, !nolock );
				if ( LDAP_SUCCESS != rc ) {
					goto cleanup_and_return;
				}
			}
		}
	}


	asip->asi_flags &= ~SLAPI_ATTR_FLAG_NOLOCKING;

	asip->asi_flags &= ~SLAPI_ATTR_FLAG_OVERRIDE;

	attr_syntax_add_by_oid( asip->asi_oid, asip, !nolock);
	attr_syntax_add_by_name( asip, !nolock);

cleanup_and_return:
	attr_syntax_return_locking_optional( oldas_from_oid, !nolock );
	attr_syntax_return_locking_optional( oldas_from_name, !nolock );
	return rc;
}
