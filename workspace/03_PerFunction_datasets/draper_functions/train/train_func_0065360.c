validator_start_download ( struct validator *validator,
				      const struct asn1_cursor *issuer ) {
	const char *crosscert;
	char *crosscert_copy;
	char *uri_string;
	size_t uri_string_len;
	uint32_t crc;
	int len;
	int rc;


	len = fetch_string_setting_copy ( NULL, &crosscert_setting,
					  &crosscert_copy );
	if ( len < 0 ) {
		rc = len;
		DBGC ( validator, "VALIDATOR %p could not fetch crosscert "
		       "setting: %s\n", validator, strerror ( rc ) );
		goto err_fetch_crosscert;
	}
	crosscert = ( crosscert_copy ? crosscert_copy : crosscert_default );


	uri_string_len = ( strlen ( crosscert ) + 22
			   + base64_encoded_len ( issuer->len ) + 1  );
	uri_string = zalloc ( uri_string_len );
	if ( ! uri_string ) {
		rc = -ENOMEM;
		goto err_alloc_uri_string;
	}


	crc = crc32_le ( 0xffffffffUL, issuer->data, issuer->len );


	len = snprintf ( uri_string, uri_string_len, "%s/%08x.der?subject=",
			 crosscert, crc );
	base64_encode ( issuer->data, issuer->len, ( uri_string + len ) );
	DBGC ( validator, "VALIDATOR %p downloading cross-signed certificate "
	       "from %s\n", validator, uri_string );


	validator->done = validator_append;


	if ( ( rc = xfer_open_uri_string ( &validator->xfer,
					   uri_string ) ) != 0 ) {
		DBGC ( validator, "VALIDATOR %p could not open %s: %s\n",
		       validator, uri_string, strerror ( rc ) );
		goto err_open_uri_string;
	}


	rc = 0;

 err_open_uri_string:
	free ( uri_string );
 err_alloc_uri_string:
	free ( crosscert_copy );
 err_fetch_crosscert:
	return rc;
}
