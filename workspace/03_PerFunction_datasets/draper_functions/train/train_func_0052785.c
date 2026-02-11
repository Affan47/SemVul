xmlSecGnuTLSAppInit(const char* config) {
    int err;

    err = gnutls_global_init();
    if(err != GNUTLS_E_SUCCESS) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "gnutls_global_init",
                    XMLSEC_ERRORS_R_CRYPTO_FAILED,
                    XMLSEC_GNUTLS_REPORT_ERROR(err));
        return(-1);
    }

    return(xmlSecGCryptAppInit(config));
}
