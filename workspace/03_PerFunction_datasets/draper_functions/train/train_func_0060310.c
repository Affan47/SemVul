_adcli_krb5_keytab_discover_salt (krb5_context k5,
                                  krb5_principal principal,
                                  krb5_kvno kvno,
                                  krb5_data *password,
                                  krb5_enctype *enctypes,
                                  krb5_data *salts,
                                  int *discovered)
{
	krb5_keytab scratch;
	krb5_error_code code;
	int i;


	code = krb5_kt_resolve (k5, "MEMORY:adcli-discover-salt", &scratch);
	return_val_if_fail (code == 0, code);

	for (i = 0; salts[i].data != NULL; i++) {
		code = _adcli_krb5_keytab_test_salt (k5, scratch, principal, kvno,
		                                     password, enctypes, &salts[i]);
		if (code == 0) {
			*discovered = i;
			break;
		} else if (code != KRB5_PREAUTH_FAILED && code != KRB5KDC_ERR_PREAUTH_FAILED) {
			break;
		}
	}

	krb5_kt_close (k5, scratch);
	return code;
}
