apreq_post_initialize(apr_pool_t *pool)
{
    (void)pool;

    if (default_parser_pool == NULL)
        return APREQ_ERROR_GENERAL;

    default_parsers_lock = 1;
    return APR_SUCCESS;
}
