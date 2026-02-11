krb5_responder_otp_get_challenge(krb5_context ctx,
                                 krb5_responder_context rctx,
                                 krb5_responder_otp_challenge **chl)
{
    const char *answer;
    krb5_responder_otp_challenge *challenge;

    answer = krb5_responder_get_challenge(ctx, rctx,
                                          KRB5_RESPONDER_QUESTION_OTP);
    if (answer == NULL) {
        *chl = NULL;
        return 0;
    }

    challenge = codec_decode_challenge(ctx, answer);
    if (challenge == NULL)
        return ENOMEM;

    *chl = challenge;
    return 0;
}
