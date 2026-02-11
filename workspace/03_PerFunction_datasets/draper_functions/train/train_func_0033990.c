check_expiration(struct webauth_context *ctx, time_t expiration)
{
    time_t now;
    int s = WA_ERR_NONE;

    now = time(NULL);
    if (expiration < now) {
        s = WA_ERR_TOKEN_EXPIRED;
        wai_error_set(ctx, s, "expired at %lu", (unsigned long) expiration);
    }
    return s;
}
