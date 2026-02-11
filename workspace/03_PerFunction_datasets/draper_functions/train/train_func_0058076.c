print_paged_results( LDAP *ld, LDAPControl *ctrl )
{
	ber_int_t estimate;


	if ( ldap_parse_pageresponse_control( ld, ctrl, &estimate, &pr_cookie )
		!= LDAP_SUCCESS )
	{

		return 1;

	} else {

		char	buf[ BUFSIZ ], *ptr = buf;

		if ( estimate > 0 ) {
			ptr += snprintf( ptr, sizeof( buf ) - ( ptr - buf ),
				"estimate=%d", estimate );
		}

		if ( pr_cookie.bv_len > 0 ) {
			struct berval	bv;

			bv.bv_len = LUTIL_BASE64_ENCODE_LEN(
				pr_cookie.bv_len ) + 1;
			bv.bv_val = ber_memalloc( bv.bv_len + 1 );

			bv.bv_len = lutil_b64_ntop(
				(unsigned char *) pr_cookie.bv_val,
				pr_cookie.bv_len,
				bv.bv_val, bv.bv_len );

			ptr += snprintf( ptr, sizeof( buf ) - ( ptr - buf ),
				"%scookie=%s", ptr == buf ? "" : " ",
				bv.bv_val );

			ber_memfree( bv.bv_val );

			pr_morePagedResults = 1;

		} else {
			ptr += snprintf( ptr, sizeof( buf ) - ( ptr - buf ),
				"%scookie=", ptr == buf ? "" : " " );
		}

		tool_write_ldif( ldif ? LDIF_PUT_COMMENT : LDIF_PUT_VALUE,
			ldif ? "pagedresults: " : "pagedresults",
			buf, ptr - buf );
	}

	return 0;
}
