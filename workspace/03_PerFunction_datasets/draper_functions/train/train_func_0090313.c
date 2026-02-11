ps_get_key_by_pub(TSS_HCONTEXT tspContext, UINT32 pub_size, BYTE *pub, TSS_HKEY *hKey)
{
	int fd;
	TSS_RESULT result = TSS_SUCCESS;
	BYTE key[4096];
	TSS_UUID uuid;

	if ((result = get_file(&fd)))
		return result;

	if ((result = psfile_get_key_by_pub(fd, &uuid, pub_size, pub, key))) {
		put_file(fd);
		return result;
	}

	put_file(fd);

	result = obj_rsakey_add_by_key(tspContext, &uuid, key, TSS_OBJ_FLAG_USER_PS, hKey);

	return result;
}
