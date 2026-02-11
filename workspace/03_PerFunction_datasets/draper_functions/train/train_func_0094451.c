set_psk(SSL *ssl __attribute__((__unused__)),
        const char *hint __attribute__((__unused__)),
        char *identity,
        unsigned int max_identity_len,
        unsigned char *password,
        unsigned int max_password_len)
{
	char *configured_id = conf_getstr(cfg, "identity");
	char *configured_pw = conf_getstr(cfg, "password");
	size_t identity_len = MIN(strlen(configured_id), max_identity_len - 1);
	size_t password_len = MIN(strlen(configured_pw), max_password_len);

	(void)memcpy(identity, configured_id, identity_len);
	(void)memcpy(password, configured_pw, password_len);

	identity[identity_len] = '\0';

	return (unsigned int)password_len;
}
