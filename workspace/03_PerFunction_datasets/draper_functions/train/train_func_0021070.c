build_token_array(struct webauth_context *ctx,
                  const apr_array_header_t *source)
{
    size_t n, size;

    n = (source == NULL) ? 0 : source->nelts;
    size = sizeof(struct webauth_token *);
    return apr_array_make(ctx->pool, n + 1, size);
}
