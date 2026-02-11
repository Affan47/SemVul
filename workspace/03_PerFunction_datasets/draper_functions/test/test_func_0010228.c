rb_ssl_shutdown(rb_fde_t *F)
{
	int i;
	if(F == NULL || F->ssl == NULL)
		return;
	for(i = 0; i < 4; i++)
	{
		if(gnutls_bye(SSL_P(F), GNUTLS_SHUT_RDWR) == GNUTLS_E_SUCCESS)
			break;
	}
	gnutls_deinit(SSL_P(F));
	rb_free(F->ssl);
}
