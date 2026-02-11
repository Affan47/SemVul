VERITY_activate(struct crypt_device *cd,
		     const char *name,
		     const char *root_hash,
		     size_t root_hash_size,
		     struct crypt_params_verity *verity_hdr,
		     uint32_t activation_flags)
{
	struct crypt_dm_active_device dmd;
	int r;

	log_dbg("Trying to activate VERITY device %s using hash %s.",
		name ?: "[none]", verity_hdr->hash_name);

	if (verity_hdr->flags & CRYPT_VERITY_CHECK_HASH) {
		log_dbg("Verification of data in userspace required.");
		r = VERITY_verify(cd, verity_hdr,
				  root_hash, root_hash_size);
		if (r < 0)
			return r;
	}

	if (!name)
		return 0;

	dmd.target = DM_VERITY;
	dmd.data_device = crypt_data_device(cd);
	dmd.u.verity.hash_device = crypt_metadata_device(cd);
	dmd.u.verity.root_hash = root_hash;
	dmd.u.verity.root_hash_size = root_hash_size;
	dmd.u.verity.hash_offset = VERITY_hash_offset_block(verity_hdr),
	dmd.flags = activation_flags;
	dmd.size = verity_hdr->data_size * verity_hdr->data_block_size / 512;
	dmd.uuid = crypt_get_uuid(cd);
	dmd.u.verity.vp = verity_hdr;

	r = device_block_adjust(cd, dmd.u.verity.hash_device, DEV_OK,
				0, NULL, NULL);
	if (r)
		return r;

	r = device_block_adjust(cd, dmd.data_device, DEV_EXCL,
				0, &dmd.size, &dmd.flags);
	if (r)
		return r;

	r = dm_create_device(cd, name, CRYPT_VERITY, &dmd, 0);
	if (r < 0 && !(dm_flags() & DM_VERITY_SUPPORTED)) {
		log_err(cd, _("Kernel doesn't support dm-verity mapping.\n"));
		return -ENOTSUP;
	}
	if (r < 0)
		return r;

	r = dm_status_verity_ok(cd, name);
	if (r < 0)
		return r;

	if (!r)
		log_err(cd, _("Verity device detected corruption after activation.\n"));
	return 0;
}
