check_cred(struct webauth_context *ctx, const struct webauth_token_cred *cred,
           enum encode_mode mode)
{
    CHECK_STR( cred, subject);
    CHECK_STR( cred, type);
    CHECK_STR( cred, service);
    CHECK_DATA(cred, data);
    CHECK_EXP( cred, expiration, mode);
    return check_cred_type(ctx, cred->type);
}
