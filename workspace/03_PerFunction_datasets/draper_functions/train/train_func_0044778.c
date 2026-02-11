_crypt_load_tcrypt(struct crypt_device *cd, struct crypt_params_tcrypt *params)
{
	int r;

	if (!params)
		return -EINVAL;

	r = init_crypto(cd);
	if (r < 0)
		return r;

	memcpy(&cd->u.tcrypt.params, params, sizeof(*params));

	r = TCRYPT_read_phdr(cd, &cd->u.tcrypt.hdr, &cd->u.tcrypt.params);

	cd->u.tcrypt.params.passphrase = NULL;
	cd->u.tcrypt.params.passphrase_size = 0;
	cd->u.tcrypt.params.keyfiles = NULL;
	cd->u.tcrypt.params.keyfiles_count = 0;

	if (r < 0)
		return r;

	if (!cd->type && !(cd->type = strdup(CRYPT_TCRYPT)))
		return -ENOMEM;

	return r;
}
