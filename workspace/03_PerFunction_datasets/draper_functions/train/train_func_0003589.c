ad_server_free(ad_server_t *server) {
    if (server == NULL) return;

    int thread = ad_server_get_option_int(server, "server.thread");
    if (thread && server->thread) {
        notify_loopexit(server);
        sleep(1);
        close_server(server);
    }

    if (server->evbase) {
        event_base_free(server->evbase);
    }

    if (server->sslctx) {
        SSL_CTX_free(server->sslctx);
        ERR_clear_error();
        ERR_remove_state(0);
    }

    if (server->options) {
        server->options->free(server->options);
    }
    if (server->stats) {
        server->stats->free(server->stats);
    }
    if (server->hooks) {
        qlist_t *tbl = server->hooks;
        ad_hook_t *hook;
        while ((hook = tbl->popfirst(tbl, NULL))) {
            if (hook->method) free(hook->method);
            free(hook);
        }
        server->hooks->free(server->hooks);
    }
    free(server);
    DEBUG("Server terminated.");
}
