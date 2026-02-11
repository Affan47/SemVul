crypt_keyslot_destroy(struct crypt_device *cd, int keyslot)
{
	crypt_keyslot_info ki;

	log_dbg("Destroying keyslot %d.", keyslot);

	if (!isLUKS(cd->type)) {
		log_err(cd, _("This operation is supported only for LUKS device.\n"));
		return -EINVAL;
	}

	ki = crypt_keyslot_status(cd, keyslot);
	if (ki == CRYPT_SLOT_INVALID) {
		log_err(cd, _("Key slot %d is invalid.\n"), keyslot);
		return -EINVAL;
	}

	if (ki == CRYPT_SLOT_INACTIVE) {
		log_err(cd, _("Key slot %d is not used.\n"), keyslot);
		return -EINVAL;
	}

	return LUKS_del_key(cd->device, keyslot, &cd->hdr, cd);
}
