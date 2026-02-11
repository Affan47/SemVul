crypt_luksAddKey(struct crypt_options *options)
{
	struct crypt_device *cd = NULL;
	int r = -EINVAL;

	r = _crypt_init(&cd, CRYPT_LUKS1, options, 1, 1);
	if (r)
		return r;

	if (options->key_file || options->new_key_file)
		r = crypt_keyslot_add_by_keyfile(cd, options->key_slot,
						 options->key_file, 0,
						 options->new_key_file, 0);
	else
		r = crypt_keyslot_add_by_passphrase(cd, options->key_slot,
						    NULL, 0, NULL, 0);

	crypt_free(cd);
	return (r < 0) ? r : 0;
}
