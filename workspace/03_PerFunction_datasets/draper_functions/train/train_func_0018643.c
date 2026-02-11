encts_process(krb5_context context, krb5_clpreauth_moddata moddata,
              krb5_clpreauth_modreq modreq, krb5_get_init_creds_opt *opt,
              krb5_clpreauth_callbacks cb, krb5_clpreauth_rock rock,
              krb5_kdc_req *request, krb5_data *encoded_request_body,
              krb5_data *encoded_previous_request, krb5_pa_data *padata,
              krb5_prompter_fct prompter, void *prompter_data,
              krb5_pa_data ***out_padata)
{
    krb5_error_code ret;
    krb5_pa_enc_ts pa_enc;
    krb5_data *ts = NULL, *enc_ts = NULL;
    krb5_enc_data enc_data;
    krb5_pa_data **pa = NULL;
    krb5_keyblock *as_key;

    enc_data.ciphertext = empty_data();

    ret = cb->get_as_key(context, rock, &as_key);
    if (ret)
        goto cleanup;
    TRACE_PREAUTH_ENC_TS_KEY_GAK(context, as_key);


    ret = cb->get_preauth_time(context, rock, TRUE, &pa_enc.patimestamp,
                               &pa_enc.pausec);
    if (ret)
        goto cleanup;

    ret = encode_krb5_pa_enc_ts(&pa_enc, &ts);
    if (ret)
        goto cleanup;

    ret = krb5_encrypt_helper(context, as_key, KRB5_KEYUSAGE_AS_REQ_PA_ENC_TS,
                              ts, &enc_data);
    if (ret)
        goto cleanup;
    TRACE_PREAUTH_ENC_TS(context, pa_enc.patimestamp, pa_enc.pausec,
                         ts, &enc_data.ciphertext);

    ret = encode_krb5_enc_data(&enc_data, &enc_ts);
    if (ret)
        goto cleanup;

    pa = k5calloc(2, sizeof(krb5_pa_data *), &ret);
    if (pa == NULL)
        goto cleanup;

    pa[0] = k5alloc(sizeof(krb5_pa_data), &ret);
    if (pa[0] == NULL)
        goto cleanup;

    pa[0]->magic = KV5M_PA_DATA;
    pa[0]->pa_type = KRB5_PADATA_ENC_TIMESTAMP;
    pa[0]->length = enc_ts->length;
    pa[0]->contents = (krb5_octet *) enc_ts->data;
    enc_ts->data = NULL;
    pa[1] = NULL;
    *out_padata = pa;
    pa = NULL;

cleanup:
    krb5_free_data(context, ts);
    krb5_free_data(context, enc_ts);
    free(enc_data.ciphertext.data);
    free(pa);
    return ret;
}
