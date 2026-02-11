ps_is_key_registered(TCPA_STORE_PUBKEY *pub)
{
	TSS_UUID *uuid;
	int fd;
	TSS_RESULT rc;
	TSS_BOOL is_reg = FALSE;

	if ((fd = get_file()) < 0)
		return FALSE;

	if ((rc = psfile_get_uuid_by_pub(fd, pub, &uuid))) {
		put_file(fd);
		return FALSE;
	}

	put_file(fd);

	if ((isUUIDRegistered(uuid, &is_reg)))
		is_reg = FALSE;

	free(uuid);
	return is_reg;
}
