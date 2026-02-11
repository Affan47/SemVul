_crypt_format_plain(struct crypt_device *cd,
			       const char *cipher,
			       const char *cipher_mode,
			       const char *uuid,
			       struct crypt_params_plain *params)
{
	if (!cipher || !cipher_mode) {
		log_err(cd, _("Invalid plain crypt parameters.\n"));
		return -EINVAL;
	}

	if (cd->volume_key->keyLength > 1024) {
		log_err(cd, _("Invalid key size.\n"));
		return -EINVAL;
	}

	cd->plain_cipher = strdup(cipher);
	cd->plain_cipher_mode = strdup(cipher_mode);

	if (uuid)
		cd->plain_uuid = strdup(uuid);

	if (params && params->hash)
		cd->plain_hdr.hash = strdup(params->hash);

	cd->plain_hdr.offset = params ? params->offset : 0;
	cd->plain_hdr.skip = params ? params->skip : 0;

	if (!cd->plain_cipher || !cd->plain_cipher_mode)
		return -ENOMEM;

	return 0;
}
