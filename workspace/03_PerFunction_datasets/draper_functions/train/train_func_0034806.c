clpreauth_tryagain(krb5_context context, clpreauth_handle h,
                   krb5_get_init_creds_opt *opt, krb5_clpreauth_callbacks cb,
                   krb5_clpreauth_rock rock, krb5_kdc_req *req,
                   krb5_data *req_body, krb5_data *prev_req,
                   krb5_preauthtype pa_type, krb5_error *error,
                   krb5_pa_data **error_padata, krb5_prompter_fct prompter,
                   void *prompter_data, krb5_pa_data ***pa_data_out)
{
    if (h->vt.tryagain == NULL)
        return 0;
    return h->vt.tryagain(context, h->data, h->req, opt, cb, rock, req,
                          req_body, prev_req, pa_type, error, error_padata,
                          prompter, prompter_data, pa_data_out);
}
