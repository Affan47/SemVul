socket_start_tls( conn_t *conn, void (*cb)( int ok, void *aux ) )
{
	static int ssl_inited;

	conn->callbacks.starttls = cb;

	if (!ssl_inited) {
		SSL_library_init();
		SSL_load_error_strings();
		ssl_data_idx = SSL_get_ex_new_index( 0, NULL, NULL, NULL, NULL );
		ssl_inited = 1;
	}

	if (!init_ssl_ctx( conn->conf )) {
		start_tls_p3( conn, 0 );
		return;
	}

	conn->ssl = SSL_new( ((server_conf_t *)conn->conf)->SSLContext );
	SSL_set_fd( conn->ssl, conn->fd );
	SSL_set_mode( conn->ssl, SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER );
	SSL_set_ex_data( conn->ssl, ssl_data_idx, conn );
	conn->state = SCK_STARTTLS;
	start_tls_p2( conn );
}
