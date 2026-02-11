crypt_volume_key_verify(struct crypt_device *cd,
	const char *volume_key,
	size_t volume_key_size)
{
	struct luks_masterkey *mk;
	int r;

	if (!isLUKS(cd->type)) {
		log_err(cd, _("This operation is supported only for LUKS device.\n"));
		return -EINVAL;
	}

	mk = LUKS_alloc_masterkey(volume_key_size, volume_key);
	if (!mk)
		return -ENOMEM;

	r = LUKS_verify_master_key(&cd->hdr, mk);

	if (r == -EPERM)
		log_err(cd, _("Volume key does not match the volume.\n"));

	LUKS_dealloc_masterkey(mk);

	return r;
}
