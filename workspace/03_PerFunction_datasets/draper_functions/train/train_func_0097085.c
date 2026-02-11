pkinit_identity_prompt(krb5_context context,
                       pkinit_plg_crypto_context plg_cryptoctx,
                       pkinit_req_crypto_context req_cryptoctx,
                       pkinit_identity_opts *idopts,
                       pkinit_identity_crypto_context id_cryptoctx,
                       krb5_clpreauth_callbacks cb,
                       krb5_clpreauth_rock rock,
                       int do_matching,
                       krb5_principal princ)
{
    krb5_error_code retval = EINVAL;
    const char *signer_identity;
    int i;

    pkiDebug("%s: %p %p %p\n", __FUNCTION__, context, idopts, id_cryptoctx);
    if (!(princ &&
          krb5_principal_compare_any_realm(context, princ,
                                           krb5_anonymous_principal()))) {
        retval = crypto_load_certs(context, plg_cryptoctx, req_cryptoctx,
                                   idopts, id_cryptoctx, princ, FALSE);
        if (retval)
            goto errout;

        if (do_matching) {


            retval = pkinit_cert_matching(context, plg_cryptoctx,
                                          req_cryptoctx, id_cryptoctx, princ);
            if (retval) {
                pkiDebug("%s: No matching certificate found\n", __FUNCTION__);
                crypto_free_cert_info(context, plg_cryptoctx, req_cryptoctx,
                                      id_cryptoctx);
                goto errout;
            }
        } else {


            retval = crypto_cert_select_default(context, plg_cryptoctx,
                                                req_cryptoctx, id_cryptoctx);
            if (retval) {
                pkiDebug("%s: Failed while selecting default certificate\n",
                         __FUNCTION__);
                crypto_free_cert_info(context, plg_cryptoctx, req_cryptoctx,
                                      id_cryptoctx);
                goto errout;
            }
        }

        if (rock != NULL && cb != NULL && retval == 0) {

            if (crypto_retrieve_signer_identity(context, id_cryptoctx,
                                                &signer_identity) == 0) {
                cb->set_cc_config(context, rock, "X509_user_identity",
                                  signer_identity);
            }
        }

        retval = crypto_free_cert_info(context, plg_cryptoctx, req_cryptoctx,
                                       id_cryptoctx);
        if (retval)
            goto errout;
    }

    for (i = 0; idopts->anchors != NULL && idopts->anchors[i] != NULL; i++) {
        retval = process_option_ca_crl(context, plg_cryptoctx, req_cryptoctx,
                                       idopts, id_cryptoctx,
                                       idopts->anchors[i], CATYPE_ANCHORS);
        if (retval)
            goto errout;
    }
    for (i = 0; idopts->intermediates != NULL
             && idopts->intermediates[i] != NULL; i++) {
        retval = process_option_ca_crl(context, plg_cryptoctx, req_cryptoctx,
                                       idopts, id_cryptoctx,
                                       idopts->intermediates[i],
                                       CATYPE_INTERMEDIATES);
        if (retval)
            goto errout;
    }
    for (i = 0; idopts->crls != NULL && idopts->crls[i] != NULL; i++) {
        retval = process_option_ca_crl(context, plg_cryptoctx, req_cryptoctx,
                                       idopts, id_cryptoctx, idopts->crls[i],
                                       CATYPE_CRLS);
        if (retval)
            goto errout;
    }
    if (idopts->ocsp != NULL) {
        retval = ENOTSUP;
        goto errout;
    }

errout:
    return retval;
}
