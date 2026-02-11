ssl_new_with_certs(SSL_CTX *ctx)
{
    SSL *ssl;

    g_return_val_if_fail(ctx != NULL, NULL);

    if(SSL_CTX_use_certificate_file(ctx, CCERT_DIR"/client_cert",
                                    SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
    }

    if(SSL_CTX_use_PrivateKey_file(ctx, CCERT_DIR"/client_key",
                                   SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
    }

    if (!SSL_CTX_load_verify_locations(ctx, NULL, CERTS_DIR)) {
        ERR_print_errors_fp(stderr);
    }

    if (!(ssl = SSL_new(ctx))) {
        hybrid_debug_error("ssl", "create SSl:%s",
                           ERR_reason_error_string(ERR_get_error()));
        return NULL;
    }

    return ssl;

}
