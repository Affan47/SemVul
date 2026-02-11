istgt_lu_parse_media_size(const char *file, const char *size, int *flags)
{
	uint64_t msize, fsize;

	ISTGT_TRACELOG(ISTGT_TRACE_DEBUG, "msize=%s\n", size);
	if (strcasecmp(file, "/dev/null") == 0) {
		return 0;
	}
	if (strcasecmp(size, "Auto") == 0
	    || strcasecmp(size, "Size") == 0) {
		msize = istgt_lu_get_filesize(file);
		if (msize == 0) {
			msize = ISTGT_LU_MEDIA_SIZE_MIN;
		}
		*flags |= ISTGT_LU_FLAG_MEDIA_AUTOSIZE;
	} else {
		msize = istgt_lu_parse_size(size);
		if (*flags & ISTGT_LU_FLAG_MEDIA_EXTEND) {
			fsize = istgt_lu_get_filesize(file);
			if (fsize > msize) {
				msize = fsize;
			}
		}
	}

	if (*flags & ISTGT_LU_FLAG_MEDIA_DYNAMIC) {
		if (msize < ISTGT_LU_MEDIA_SIZE_MIN) {
			msize = ISTGT_LU_MEDIA_SIZE_MIN;
		}
	} else {
		if (msize < ISTGT_LU_MEDIA_SIZE_MIN) {
			ISTGT_ERRLOG("media size too small\n");
			return 0ULL;
		}
	}

	return msize;
}
