write_service_token_cache(server_rec *server, struct server_config *sconf,
                          MWA_SERVICE_TOKEN *token)
{
    struct webauth_was_token_cache cache;
    int status;


    memset(&cache, 0, sizeof(cache));
    cache.token = token->token;
    cache.key_type = token->key.type;
    cache.key_data = token->key.data;
    cache.key_data_len = token->key.length;
    cache.created = token->created;
    cache.expires = token->expires;
    cache.last_renewal = token->last_renewal_attempt;
    cache.next_renewal = token->next_renewal_attempt;


    status = webauth_was_token_cache_write(sconf->ctx, &cache,
                                           sconf->st_cache_path);
    if (status != WA_ERR_NONE) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, server,
                     "mod_webauth: cannot write service token cache %s: %s",
                     sconf->st_cache_path,
                     webauth_error_message(sconf->ctx, status));
        return 0;
    }
    return 1;
}
