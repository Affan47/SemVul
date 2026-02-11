send_finished(SSL *ssl)
{
    uint8_t buf[SSL_FINISHED_HASH_SIZE+4] = {
        HS_FINISHED, 0, 0, SSL_FINISHED_HASH_SIZE };


    finished_digest(ssl,
        IS_SET_SSL_FLAG(SSL_IS_CLIENT) ?
                    client_finished : server_finished, &buf[4]);

#ifndef CONFIG_SSL_SKELETON_MODE

    if (!IS_SET_SSL_FLAG(SSL_SESSION_RESUME) && ssl->ssl_ctx->num_sessions)
    {
        memcpy(ssl->session->master_secret,
                ssl->dc->master_secret, SSL_SECRET_SIZE);
    }
#endif

    return send_packet(ssl, PT_HANDSHAKE_PROTOCOL,
                                buf, SSL_FINISHED_HASH_SIZE+4);
}
