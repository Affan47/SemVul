istgt_lu_dvd_unload_media(ISTGT_LU_DVD *spec)
{
	int64_t rc;

	if (!istgt_lu_dvd_media_present(spec)
		&& !spec->mchanged) {

		return 0;
	}
	if (istgt_lu_dvd_media_lock(spec)) {
		return -1;
	}

	if (!spec->lu->readonly
		&& !(spec->mflags & ISTGT_LU_FLAG_MEDIA_READONLY)) {
		rc = istgt_lu_dvd_sync(spec, 0, spec->size);
		if (rc < 0) {
			ISTGT_ERRLOG("lu_dvd_sync() failed\n");
			return -1;
		}
	}
	rc = (int64_t) istgt_lu_dvd_close(spec);
	if (rc < 0) {
		ISTGT_ERRLOG("lu_dvd_close() failed\n");
		return -1;
	}

	spec->file = NULL;
	spec->size = 0;
	spec->mflags = 0;
	spec->blocklen = DEFAULT_DVD_BLOCKLEN;
	spec->blockcnt = spec->size / spec->blocklen;
	spec->profile = DEFAULT_DVD_PROFILE;

	spec->mload = 0;
	spec->mchanged = 0;
	spec->mwait = 3;
	return 0;
}
