crypt_resume_by_passphrase(struct crypt_device *cd,
			       const char *name,
			       int keyslot,
			       const char *passphrase,
			       size_t passphrase_size)
{
	struct luks_masterkey *mk = NULL;
	int r, suspended = 0;

	log_dbg("Resuming volume %s.", name);

	if (!isLUKS(cd->type)) {
		log_err(cd, _("This operation is supported only for LUKS device.\n"));
		r = -EINVAL;
		goto out;
	}

	r = dm_query_device(name, NULL, NULL, NULL, NULL,
			    NULL, NULL, NULL, NULL, &suspended, NULL);
	if (r < 0)
		return r;

	if (!suspended) {
		log_err(cd, _("Volume %s is not suspended.\n"), name);
		return -EINVAL;
	}

	if (passphrase) {
		r = LUKS_open_key_with_hdr(cd->device, keyslot, passphrase,
					   passphrase_size, &cd->hdr, &mk, cd);
	} else
		r = volume_key_by_terminal_passphrase(cd, keyslot, &mk);

	if (r >= 0) {
		keyslot = r;
		r = dm_resume_and_reinstate_key(name, mk->keyLength, mk->key);
		if (r == -ENOTSUP)
			log_err(cd, "Resume is not supported for device %s.\n", name);
		else if (r)
			log_err(cd, "Error during resuming device %s.\n", name);
	} else
		r = keyslot;
out:
	LUKS_dealloc_masterkey(mk);
	return r < 0 ? r : keyslot;
}
