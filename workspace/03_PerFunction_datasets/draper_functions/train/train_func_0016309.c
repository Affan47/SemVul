oidValidate(
	Syntax *syntax,
	struct berval *in )
{
	struct berval val = *in;

	if( val.bv_len == 0 ) {

		return LDAP_INVALID_SYNTAX;
	}

	if( DESC_LEADCHAR( val.bv_val[0] ) ) {
		val.bv_val++;
		val.bv_len--;
		if ( val.bv_len == 0 ) return LDAP_SUCCESS;

		while( DESC_CHAR( val.bv_val[0] ) ) {
			val.bv_val++;
			val.bv_len--;

			if ( val.bv_len == 0 ) return LDAP_SUCCESS;
		}

	} else {
		int sep = 0;
		while( OID_LEADCHAR( val.bv_val[0] ) ) {
			val.bv_val++;
			val.bv_len--;

			if ( val.bv_val[-1] != '0' ) {
				while ( OID_LEADCHAR( val.bv_val[0] )) {
					val.bv_val++;
					val.bv_len--;
				}
			}

			if( val.bv_len == 0 ) {
				if( sep == 0 ) break;
				return LDAP_SUCCESS;
			}

			if( !OID_SEPARATOR( val.bv_val[0] )) break;

			sep++;
			val.bv_val++;
			val.bv_len--;
		}
	}

	return LDAP_INVALID_SYNTAX;
}
