mwa_get_service_token(server_rec *server, struct server_config *sconf,
                      apr_pool_t *pool, int local_cache_only)
{
    struct webauth_context *ctx;
    MWA_SERVICE_TOKEN *token;
    time_t curr = time(NULL);
    static const char *mwa_func = "mwa_get_service_token";

    apr_thread_mutex_lock(sconf->mutex);


    webauth_context_init_apr(&ctx, pool);

    if (sconf->service_token != NULL) {

        if (sconf->service_token->next_renewal_attempt > curr) {
            token = copy_service_token(pool, sconf->service_token);
            if (sconf->debug) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, server,
                             "mod_webauth: %s: using cached service token",
                             mwa_func);
            }
            goto done;
        }

    }


    token = read_service_token_cache(server, sconf, pool);

    if (token != NULL) {

        if (sconf->debug) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, server,
                         "mod_webauth: %s: read service token from: %s",
                         mwa_func, sconf->st_cache_path);
        }


        if (token->next_renewal_attempt > curr) {


            set_app_state(ctx, server, sconf, token);

            set_service_token(token, sconf);
            goto done;
        }
    }


    if (local_cache_only)
        goto done;

    token = request_service_token(ctx, server, sconf, pool, curr);

    if (token == NULL ) {

        ap_log_error(APLOG_MARK, APLOG_ERR, 0, server,
                     "mod_webauth: %s: couldn't get new service "
                     "token from webkdc",
                     mwa_func);


        if (sconf->service_token != NULL) {


            sconf->service_token->last_renewal_attempt = curr;
            sconf->service_token->next_renewal_attempt =
                curr+TOKEN_RETRY_INTERVAL;
            write_service_token_cache(server, sconf, sconf->service_token);
        }
    } else {

        if (sconf->debug) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, server,
                         "mod_webauth: %s: got new service token from webkdc",
                         mwa_func);
        }


        write_service_token_cache(server, sconf, token);
        set_app_state(ctx, server, sconf, token);
        set_service_token(token, sconf);
        goto done;
    }

done:
    apr_thread_mutex_unlock(sconf->mutex);

    if (token == NULL && !local_cache_only) {

        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, server,
                     "mod_webauth: mwa_get_service_token FAILD!!");
    }
    return token;
}
