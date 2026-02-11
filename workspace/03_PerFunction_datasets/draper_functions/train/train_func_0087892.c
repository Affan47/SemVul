hx509_crypto_init(hx509_context context,
		  const char *provider,
		  const heim_oid *enctype,
		  hx509_crypto *crypto)
{
    const struct hx509cipher *cipher;

    *crypto = NULL;

    cipher = find_cipher_by_oid(enctype);
    if (cipher == NULL) {
	hx509_set_error_string(context, 0, HX509_ALG_NOT_SUPP,
			       "Algorithm not supported");
	return HX509_ALG_NOT_SUPP;
    }

    *crypto = calloc(1, sizeof(**crypto));
    if (*crypto == NULL) {
	hx509_clear_error_string(context);
	return ENOMEM;
    }

    (*crypto)->flags = PADDING_PKCS7;
    (*crypto)->cipher = cipher;
    (*crypto)->c = (*cipher->evp_func)();

    if (der_copy_oid(enctype, &(*crypto)->oid)) {
	hx509_crypto_destroy(*crypto);
	*crypto = NULL;
	hx509_clear_error_string(context);
	return ENOMEM;
    }

    return 0;
}
