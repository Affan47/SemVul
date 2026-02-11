crypt_resize_device(struct crypt_options *options)
{
	struct crypt_device *cd = NULL;
	char *device = NULL, *cipher = NULL, *uuid = NULL, *key = NULL;
	char *type = NULL;
	uint64_t size, skip, offset;
	int key_size, read_only, r;

	log_dbg("Resizing device %s to %" PRIu64 " sectors.", options->name, options->size);

	if (dm_init(NULL, 1) < 0)
		return -ENOSYS;

	r = dm_query_device(options->name, &device, &size, &skip, &offset,
			    &cipher, &key_size, &key, &read_only, NULL, &uuid);
	if (r < 0) {
		log_err(NULL, _("Device %s is not active.\n"), options->name);
		goto out;
	}


	type = CRYPT_PLAIN;
	if (uuid) {
		if (!strncmp(uuid, CRYPT_PLAIN, strlen(CRYPT_PLAIN))) {
			type = CRYPT_PLAIN;
			free (uuid);
			uuid = NULL;
		} else if (!strncmp(uuid, CRYPT_LUKS1, strlen(CRYPT_LUKS1)))
			type = CRYPT_LUKS1;
	}

	if (!options->device)
		options->device = device;

	r = _crypt_init(&cd, type, options, 1, 1);
	if (r)
		goto out;

	size = options->size;
	r = device_check_and_adjust(cd, device, &size, &offset, &read_only);
	if (r)
		goto out;

	r = dm_create_device(options->name, device, cipher, type,
			     crypt_get_uuid(cd), size, skip, offset,
			     key_size, key, read_only, 1);
out:
	safe_free(key);
	free(cipher);
	if (options->device == device)
		options->device = NULL;
	free(device);
	free(uuid);
	crypt_free(cd);
	dm_exit();
	return r;
}
