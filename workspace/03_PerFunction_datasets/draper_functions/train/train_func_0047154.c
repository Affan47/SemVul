set_pa_data(const krb5_pa_otp_req *req, krb5_pa_data ***pa_data_out)
{
    krb5_pa_data **out = NULL;
    krb5_data *tmp;


    out = calloc(2, sizeof(krb5_pa_data *));
    if (out == NULL)
        goto error;
    out[0] = calloc(1, sizeof(krb5_pa_data));
    out[1] = NULL;
    if (out[0] == NULL)
        goto error;


    memset(out[0], 0, sizeof(krb5_pa_data));
    out[0]->pa_type = KRB5_PADATA_OTP_REQUEST;
    if (encode_krb5_pa_otp_req(req, &tmp) != 0)
        goto error;
    out[0]->contents = (krb5_octet *)tmp->data;
    out[0]->length = tmp->length;

    *pa_data_out = out;
    return 0;

error:
    if (out != NULL) {
        free(out[0]);
        free(out);
    }
    return ENOMEM;
}
