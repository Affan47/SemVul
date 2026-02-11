pki_key_generate_rsa(ssh_key key, int parameter){
	BIGNUM *e;
	int rc;

	e = BN_new();
	key->rsa = RSA_new();

	BN_set_word(e, 65537);
	rc = RSA_generate_key_ex(key->rsa, parameter, e, NULL);

	BN_free(e);

	if (rc == -1 || key->rsa == NULL)
		return SSH_ERROR;
	return SSH_OK;
}
