init_creds_step_request(krb5_context context,
                        krb5_init_creds_context ctx,
                        krb5_data *out)
{
    krb5_error_code code;

    if (ctx->loopcount >= MAX_IN_TKT_LOOPS) {
        code = KRB5_GET_IN_TKT_LOOP;
        goto cleanup;
    }


    code = pick_nonce(context, ctx);
    if (code != 0)
        goto cleanup;


    code = set_request_times(context, ctx);
    if (code != 0)
        goto cleanup;

    krb5_free_data(context, ctx->inner_request_body);
    ctx->inner_request_body = NULL;
    code = encode_krb5_kdc_req_body(ctx->request, &ctx->inner_request_body);
    if (code)
        goto cleanup;


    read_allowed_preauth_type(context, ctx);
    ctx->selected_preauth_type = KRB5_PADATA_NONE;


    read_cc_config_in_data(context, ctx);
    clear_cc_config_out_data(context, ctx);

    if (ctx->err_reply == NULL) {

        code = k5_preauth(context, ctx, ctx->preauth_to_use,
                          ctx->preauth_required, &ctx->request->padata,
                          &ctx->selected_preauth_type);
        if (code != 0)
            goto cleanup;
    } else {
        if (ctx->preauth_to_use != NULL) {


            code = k5_preauth_tryagain(context, ctx, ctx->preauth_to_use,
                                       &ctx->request->padata);
        } else {

            code = KRB5KRB_ERR_GENERIC;
        }
        if (code != 0) {

            code = ctx->err_reply->error + ERROR_TABLE_BASE_krb5;
            goto cleanup;
        }
    }


    ctx->request_time = time(NULL);

    if (ctx->encoded_previous_request != NULL) {
        krb5_free_data(context, ctx->encoded_previous_request);
        ctx->encoded_previous_request = NULL;
    }
    if (ctx->request->padata)
        ctx->sent_nontrivial_preauth = 1;
    if (ctx->enc_pa_rep_permitted)
        code = request_enc_pa_rep(&ctx->request->padata);
    if (code)
        goto cleanup;
    code = krb5int_fast_prep_req(context, ctx->fast_state,
                                 ctx->request, ctx->outer_request_body,
                                 encode_krb5_as_req,
                                 &ctx->encoded_previous_request);
    if (code != 0)
        goto cleanup;

    code = krb5int_copy_data_contents(context,
                                      ctx->encoded_previous_request,
                                      out);
    if (code != 0)
        goto cleanup;

cleanup:
    krb5_free_pa_data(context, ctx->request->padata);
    ctx->request->padata = NULL;
    return code;
}
