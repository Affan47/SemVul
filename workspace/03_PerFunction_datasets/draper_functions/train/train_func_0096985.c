fast_parse_cookie(kdc_request_t r, const PA_DATA *pa)
{
    krb5_crypto crypto = NULL;
    krb5_error_code ret;
    KDCFastCookie data;
    krb5_data d1;
    size_t len;

    ret = decode_KDCFastCookie(pa->padata_value.data,
			       pa->padata_value.length,
			       &data, &len);
    if (ret)
	return ret;

    if (len != pa->padata_value.length || strcmp("H5L1", data.version) != 0) {
	free_KDCFastCookie(&data);
	return KRB5KDC_ERR_POLICY;
    }

    ret = get_fastuser_crypto(r, data.cookie.etype, &crypto);
    if (ret)
	goto out;

    ret = krb5_decrypt_EncryptedData(r->context, crypto,
				     KRB5_KU_H5L_COOKIE,
				     &data.cookie, &d1);
    krb5_crypto_destroy(r->context, crypto);
    if (ret)
	goto out;

    ret = decode_KDCFastState(d1.data, d1.length, &r->fast, &len);
    krb5_data_free(&d1);
    if (ret)
	goto out;

    if (r->fast.expiration < kdc_time) {
	kdc_log(r->context, r->config, 0, "fast cookie expired");
	ret = KRB5KDC_ERR_POLICY;
	goto out;
    }

 out:
    free_KDCFastCookie(&data);

    return ret;
}
