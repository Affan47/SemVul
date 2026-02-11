psfile_get_key_by_uuid(int fd, TSS_UUID *uuid, BYTE *key)
{
        int rc;
	TSS_RESULT result;
        off_t file_offset;
        struct key_disk_cache tmp;
	BYTE buf[4096];

	if ((result = psfile_get_cache_entry_by_uuid(fd, uuid, &tmp)))
		return result;


	file_offset = TSSPS_BLOB_DATA_OFFSET(&tmp);

	rc = lseek(fd, file_offset, SEEK_SET);
	if (rc == ((off_t)-1)) {
		LogDebugFn("lseek: %s", strerror(errno));
		return TSPERR(TSS_E_INTERNAL_ERROR);
	}

	if (tmp.blob_size > 4096) {
		LogError("Blob size greater than 4096! Size:  %d",
			  tmp.blob_size);
		return TSPERR(TSS_E_INTERNAL_ERROR);
	}
	if ((rc = read_data(fd, buf, tmp.blob_size))) {
		LogDebugFn("Blob read from disk failed.");
		return rc;
	}

	memcpy(key, buf, tmp.blob_size);
	return TSS_SUCCESS;
}
