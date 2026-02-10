psk_server_callback(SSL *ssl, const char *identity,
					unsigned char *psk, int max_psk_len)
{
	unsigned int psk_len;
	fr_tls_server_conf_t *conf;

	conf = (fr_tls_server_conf_t *)SSL_get_ex_data(ssl,
						       FR_TLS_EX_INDEX_CONF);
	if (!conf) return 0;


	if (strcmp(identity, conf->psk_identity) != 0) {
		return 0;
	}

	psk_len = strlen(conf->psk_password);
	if (psk_len > (2 * max_psk_len)) return 0;

	return fr_hex2bin(conf->psk_password, psk, psk_len);
}
