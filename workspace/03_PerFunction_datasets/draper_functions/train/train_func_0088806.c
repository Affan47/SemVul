x509write_create_sign(x509_raw *chain, rsa_context *privkey)
{
    int ret, serial;


    if ((ret = asn1_add_int(2, &chain->version)) != 0)
        return ret;

    if ((ret = asn1_append_tag(&chain->version, ASN1_CONTEXT_SPECIFIC |
                    ASN1_CONSTRUCTED)) != 0)
        return ret;


    srand((unsigned int) time(NULL));
    serial = rand();
    if ((ret = asn1_add_int(serial, &chain->serial)) != 0)
        return ret;


    if ((ret = asn1_add_oid(&chain->tbs_signalg,
				(unsigned char*)OID_PKCS1_RSA_SHA, 9, ASN1_CONSTRUCTED |
				ASN1_SEQUENCE, ASN1_NULL, (unsigned char*)"", 0)) != 0)
        return ret;


    if ((ret = asn1_append_nodes(&chain->tbs, ASN1_CONSTRUCTED |
                    ASN1_SEQUENCE, 7, &chain->version, &chain->serial,
                    &chain->tbs_signalg, &chain->issuer, &chain->validity,
                    &chain->subject, &chain->subpubkey)) != 0)
        return ret;


    if ((ret = x509write_make_sign(chain, privkey)) != 0)
        return ret;


    if ((ret = asn1_append_nodes(&chain->raw, ASN1_CONSTRUCTED |
                    ASN1_SEQUENCE, 3, &chain->tbs, &chain->signalg,
                    &chain->sign)) != 0)
        return ret;

    return 0;
}
