conn_wrap_fd(int fd, int ssl)
{
    Connection *conn;

    if (socket_set_blocking(fd, 0) < 0)
        return NULL;

    conn = gw_malloc(sizeof(*conn));
    conn->inlock = mutex_create();
    conn->outlock = mutex_create();
    conn->claimed = 0;

    conn->outbuf = octstr_create("");
    conn->outbufpos = 0;
    conn->inbuf = octstr_create("");
    conn->inbufpos = 0;

    conn->fd = fd;
    conn->connected = yes;
    conn->read_eof = 0;
    conn->io_error = 0;
    conn->output_buffering = DEFAULT_OUTPUT_BUFFERING;

    conn->registered = NULL;
    conn->callback = NULL;
    conn->callback_data = NULL;
    conn->callback_data_destroyer = NULL;
    conn->listening_pollin = 0;
    conn->listening_pollout = 0;
#ifdef HAVE_LIBSSL


    if (ssl) {
        conn->ssl = SSL_new(global_server_ssl_context);
        conn->peer_certificate = NULL;


        if (SSL_set_fd(conn->ssl, conn->fd) == 0) {

            error(errno, "SSL: OpenSSL: %.256s", ERR_error_string(ERR_get_error(), NULL));
            conn_destroy(conn);
            return NULL;
        }


        BIO_set_nbio(SSL_get_rbio(conn->ssl), 1);
        BIO_set_nbio(SSL_get_wbio(conn->ssl), 1);


         SSL_set_accept_state(conn->ssl);
    } else {
        conn->ssl = NULL;
        conn->peer_certificate = NULL;
    }
#endif

    return conn;
}
