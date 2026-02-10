xmlSecGnuTLSKeyDataRsaAdoptPublicKey(xmlSecKeyDataPtr data,
                                     gnutls_datum_t * m, gnutls_datum_t * e) {
    gnutls_datum_t params[2];
    gcry_mpi_t mpis[2];
    gcry_sexp_t pub_key = NULL;
    int rc;
    int ret;

    xmlSecAssert2(xmlSecKeyDataCheckId(data, xmlSecGnuTLSKeyDataRsaId), -1);
    xmlSecAssert2(m != NULL, -1);
    xmlSecAssert2(e != NULL, -1);


    memcpy(&(params[0]), m, sizeof(*m));
    memcpy(&(params[1]), e, sizeof(*e));


    ret = xmlSecGnuTLSConvertParamsToMpis(
            params, sizeof(params)/sizeof(params[0]),
            mpis, sizeof(mpis)/sizeof(mpis[0]));
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecGnuTLSConvertParamsToMpis",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);

        return(-1);
    }


    rc = gcry_sexp_build(&(pub_key), NULL, "(public-key(rsa((n%m)(e%m))))",
                        mpis[0], mpis[1]);
    if((rc != GPG_ERR_NO_ERROR) || (pub_key == NULL)) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "gcry_sexp_build(private/rsa)",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_GNUTLS_GCRYPT_REPORT_ERROR(rc));
        xmlSecGnuTLSDestroyMpis(mpis, sizeof(mpis)/sizeof(mpis[0]));
        return(-1);
    }
    xmlSecGnuTLSDestroyMpis(mpis, sizeof(mpis)/sizeof(mpis[0]));

    ret = xmlSecGCryptKeyDataRsaAdoptKeyPair(data, pub_key, NULL);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecGCryptKeyDataRsaAdoptKeyPair",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        gcry_sexp_release(pub_key);
        return(-1);
    }


    gnutls_free(m->data);
    gnutls_free(e->data);
    return(0);
}
