process_option_ca_crl(krb5_context context,
                      pkinit_plg_crypto_context plg_cryptoctx,
                      pkinit_req_crypto_context req_cryptoctx,
                      pkinit_identity_opts *idopts,
                      pkinit_identity_crypto_context id_cryptoctx,
                      const char *value,
                      int catype)
{
    char *residual;
    unsigned int typelen;
    int idtype;

    pkiDebug("%s: processing catype %s, value '%s'\n",
             __FUNCTION__, catype2string(catype), value);
    residual = strchr(value, ':');
    if (residual == NULL) {
        pkiDebug("No type given for '%s'\n", value);
        return EINVAL;
    }
    residual++;
    typelen = residual - value;
    if (strncmp(value, "FILE:", typelen) == 0) {
        idtype = IDTYPE_FILE;
    } else if (strncmp(value, "DIR:", typelen) == 0) {
        idtype = IDTYPE_DIR;
#ifdef PKINIT_CRYPTO_IMPL_NSS
    } else if (strncmp(value, "NSS:", typelen) == 0) {
        idtype = IDTYPE_NSS;
#endif
    } else {
        return ENOTSUP;
    }
    return crypto_load_cas_and_crls(context,
                                    plg_cryptoctx,
                                    req_cryptoctx,
                                    idopts, id_cryptoctx,
                                    idtype, catype, residual);
}
