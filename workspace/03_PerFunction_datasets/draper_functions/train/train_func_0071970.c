pkinit_client_tryagain(krb5_context context, krb5_clpreauth_moddata moddata,
                       krb5_clpreauth_modreq modreq,
                       krb5_get_init_creds_opt *gic_opt,
                       krb5_clpreauth_callbacks cb, krb5_clpreauth_rock rock,
                       krb5_kdc_req *request, krb5_data *encoded_request_body,
                       krb5_data *encoded_previous_request,
                       krb5_preauthtype pa_type, krb5_error *err_reply,
                       krb5_pa_data **err_padata, krb5_prompter_fct prompter,
                       void *prompter_data, krb5_pa_data ***out_padata)
{
    krb5_error_code retval = KRB5KDC_ERR_PREAUTH_FAILED;
    pkinit_context plgctx = (pkinit_context)moddata;
    pkinit_req_context reqctx = (pkinit_req_context)modreq;
    krb5_pa_data *pa;
    krb5_data scratch;
    krb5_external_principal_identifier **certifiers = NULL;
    krb5_algorithm_identifier **algId = NULL;
    int do_again = 0;

    pkiDebug("pkinit_client_tryagain %p %p %p %p\n",
             context, plgctx, reqctx, request);

    if (reqctx->pa_type != pa_type || err_padata == NULL)
        return retval;

    for (; *err_padata != NULL && !do_again; err_padata++) {
        pa = *err_padata;
        PADATA_TO_KRB5DATA(pa, &scratch);
        switch (pa->pa_type) {
        case TD_TRUSTED_CERTIFIERS:
        case TD_INVALID_CERTIFICATES:
            retval = k5int_decode_krb5_td_trusted_certifiers(&scratch,
                                                             &certifiers);
            if (retval) {
                pkiDebug("failed to decode sequence of trusted certifiers\n");
                goto cleanup;
            }
            retval = pkinit_process_td_trusted_certifiers(context,
                                                          plgctx->cryptoctx,
                                                          reqctx->cryptoctx,
                                                          reqctx->idctx,
                                                          certifiers,
                                                          pa->pa_type);
            if (!retval)
                do_again = 1;
            break;
        case TD_DH_PARAMETERS:
            retval = k5int_decode_krb5_td_dh_parameters(&scratch, &algId);
            if (retval) {
                pkiDebug("failed to decode td_dh_parameters\n");
                goto cleanup;
            }
            retval = pkinit_process_td_dh_params(context, plgctx->cryptoctx,
                                                 reqctx->cryptoctx,
                                                 reqctx->idctx, algId,
                                                 &reqctx->opts->dh_size);
            if (!retval)
                do_again = 1;
            break;
        default:
            break;
        }
    }

    if (do_again) {
        TRACE_PKINIT_CLIENT_TRYAGAIN(context);
        retval = pa_pkinit_gen_req(context, plgctx, reqctx, request, pa_type,
                                   out_padata, prompter, prompter_data,
                                   gic_opt);
        if (retval)
            goto cleanup;
    }

    retval = 0;
cleanup:
    if (certifiers != NULL)
        free_krb5_external_principal_identifier(&certifiers);

    if (algId != NULL)
        free_krb5_algorithm_identifiers(&algId);

    pkiDebug("pkinit_client_tryagain: returning %d (%s)\n",
             retval, error_message(retval));
    return retval;
}
