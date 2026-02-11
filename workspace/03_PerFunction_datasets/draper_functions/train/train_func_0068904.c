otp_client_request_fini(krb5_context context, krb5_clpreauth_moddata moddata,
                        krb5_clpreauth_modreq modreq)
{
    if (modreq == NULL)
        return;

    k5_free_pa_otp_challenge(context, *(krb5_pa_otp_challenge **)modreq);
    free(modreq);
}
