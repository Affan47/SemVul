p12_store(hx509_context context,
	  hx509_certs certs, void *data, int flags, hx509_lock lock)
{
    struct ks_pkcs12 *p12 = data;
    PKCS12_PFX pfx;
    PKCS12_AuthenticatedSafe as;
    PKCS12_OctetString asdata;
    size_t size;
    int ret;

    memset(&as, 0, sizeof(as));
    memset(&pfx, 0, sizeof(pfx));

    ret = hx509_certs_iter_f(context, p12->certs, store_func, &as);
    if (ret)
	goto out;

    ASN1_MALLOC_ENCODE(PKCS12_AuthenticatedSafe, asdata.data, asdata.length,
		       &as, &size, ret);
    free_PKCS12_AuthenticatedSafe(&as);
    if (ret)
	return ret;

    ret = der_parse_hex_heim_integer("03", &pfx.version);
    if (ret) {
	free(asdata.data);
	goto out;
    }

    pfx.authSafe.content = calloc(1, sizeof(*pfx.authSafe.content));

    ASN1_MALLOC_ENCODE(PKCS12_OctetString,
		       pfx.authSafe.content->data,
		       pfx.authSafe.content->length,
		       &asdata, &size, ret);
    free(asdata.data);
    if (ret)
	goto out;

    ret = der_copy_oid(&asn1_oid_id_pkcs7_data, &pfx.authSafe.contentType);
    if (ret)
	goto out;

    ASN1_MALLOC_ENCODE(PKCS12_PFX, asdata.data, asdata.length,
		       &pfx, &size, ret);
    if (ret)
	goto out;

#if 0
    const struct _hx509_password *pw;

    pw = _hx509_lock_get_passwords(lock);
    if (pw != NULL) {
	pfx.macData = calloc(1, sizeof(*pfx.macData));
	if (pfx.macData == NULL) {
	    ret = ENOMEM;
	    hx509_set_error_string(context, 0, ret, "malloc out of memory");
	    return ret;
	}
	if (pfx.macData == NULL) {
	    free(asdata.data);
	    goto out;
	}
    }
    ret = calculate_hash(&aspath, pw, pfx.macData);
#endif

    rk_dumpdata(p12->fn, asdata.data, asdata.length);
    free(asdata.data);

out:
    free_PKCS12_AuthenticatedSafe(&as);
    free_PKCS12_PFX(&pfx);

    return ret;
}
