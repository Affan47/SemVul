_hx509_cert_get_keyusage(hx509_context context,
			 hx509_cert c,
			 KeyUsage *ku)
{
    Certificate *cert;
    const Extension *e;
    size_t size;
    int ret;
    size_t i = 0;

    memset(ku, 0, sizeof(*ku));

    cert = _hx509_get_cert(c);

    if (_hx509_cert_get_version(cert) < 3)
	return 0;

    e = find_extension(cert, &asn1_oid_id_x509_ce_keyUsage, &i);
    if (e == NULL)
	return HX509_KU_CERT_MISSING;

    ret = decode_KeyUsage(e->extnValue.data, e->extnValue.length, ku, &size);
    if (ret)
	return ret;
    return 0;
}
