webauth_factors_string(struct webauth_context *ctx,
                       const struct webauth_factors *factors)
{
    if (factors == NULL || apr_is_empty_array(factors->factors))
        return NULL;
    return apr_array_pstrcat(ctx->pool, factors->factors, ',');
}
