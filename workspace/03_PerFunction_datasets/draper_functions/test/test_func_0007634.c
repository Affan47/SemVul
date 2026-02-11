crypt_keyslot_change_by_passphrase(struct crypt_device *cd,
	int keyslot_old,
	int keyslot_new,
	const char *passphrase,
	size_t passphrase_size,
	const char *new_passphrase,
	size_t new_passphrase_size)
{
	struct volume_key *vk = NULL;
	int r;

	log_dbg("Changing passphrase from old keyslot %d to new %d.",
		keyslot_old, keyslot_new);

	r = onlyLUKS(cd);
	if (r < 0)
		return r;

	r = LUKS_open_key_with_hdr(keyslot_old, passphrase, passphrase_size,
				   &cd->u.luks1.hdr, &vk, cd);
	if (r < 0)
		goto out;

	if (keyslot_old != CRYPT_ANY_SLOT && keyslot_old != r) {
		log_dbg("Keyslot mismatch.");
		goto out;
	}
	keyslot_old = r;

	if (keyslot_new == CRYPT_ANY_SLOT) {
		keyslot_new = LUKS_keyslot_find_empty(&cd->u.luks1.hdr);
		if (keyslot_new < 0)
			keyslot_new = keyslot_old;
	}

	if (keyslot_old == keyslot_new) {
		log_dbg("Key slot %d is going to be overwritten.", keyslot_old);
		(void)crypt_keyslot_destroy(cd, keyslot_old);
	}

	r = LUKS_set_key(keyslot_new, new_passphrase, new_passphrase_size,
			 &cd->u.luks1.hdr, vk, cd->iteration_time,
			 &cd->u.luks1.PBKDF2_per_sec, cd);

	if (keyslot_old == keyslot_new) {
		if (r >= 0)
			log_verbose(cd, _("Key slot %d changed.\n"), r);
	} else {
		if (r >= 0) {
			log_verbose(cd, _("Replaced with key slot %d.\n"), r);
			r = crypt_keyslot_destroy(cd, keyslot_old);
		}
	}
	if (r < 0)
		log_err(cd, _("Failed to swap new key slot.\n"));
out:
	crypt_free_volume_key(vk);
	return r ?: keyslot_new;
}
