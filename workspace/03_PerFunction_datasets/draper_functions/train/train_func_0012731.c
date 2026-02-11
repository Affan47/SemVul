GetDiskFreeSpaceEx(const gunichar2 *path_name, WapiULargeInteger *free_bytes_avail,
			    WapiULargeInteger *total_number_of_bytes,
			    WapiULargeInteger *total_number_of_free_bytes)
{
#ifdef HAVE_STATVFS
	struct statvfs fsstat;
#elif defined(HAVE_STATFS)
	struct statfs fsstat;
#endif
	gboolean isreadonly;
	gchar *utf8_path_name;
	int ret;
	unsigned long block_size;

	if (path_name == NULL) {
		utf8_path_name = g_strdup (g_get_current_dir());
		if (utf8_path_name == NULL) {
			SetLastError (ERROR_DIRECTORY);
			return(FALSE);
		}
	}
	else {
		utf8_path_name = mono_unicode_to_external (path_name);
		if (utf8_path_name == NULL) {
			DEBUG("%s: unicode conversion returned NULL", __func__);

			SetLastError (ERROR_INVALID_NAME);
			return(FALSE);
		}
	}

	do {
#ifdef HAVE_STATVFS
		ret = statvfs (utf8_path_name, &fsstat);
		isreadonly = ((fsstat.f_flag & ST_RDONLY) == ST_RDONLY);
		block_size = fsstat.f_frsize;
#elif defined(HAVE_STATFS)
		ret = statfs (utf8_path_name, &fsstat);
		isreadonly = ((fsstat.f_flags & MNT_RDONLY) == MNT_RDONLY);
		block_size = fsstat.f_bsize;
#endif
	} while(ret == -1 && errno == EINTR);

	g_free(utf8_path_name);

	if (ret == -1) {
		_wapi_set_last_error_from_errno ();
		DEBUG ("%s: statvfs failed: %s", __func__, strerror (errno));
		return(FALSE);
	}


	if (free_bytes_avail != NULL) {
		if (isreadonly) {
			free_bytes_avail->QuadPart = 0;
		}
		else {
			free_bytes_avail->QuadPart = block_size * (guint64)fsstat.f_bavail;
		}
	}


	if (total_number_of_bytes != NULL) {
		total_number_of_bytes->QuadPart = block_size * (guint64)fsstat.f_blocks;
	}


	if (total_number_of_free_bytes != NULL) {
		if (isreadonly) {
			total_number_of_free_bytes->QuadPart = 0;
		}
		else {
			total_number_of_free_bytes->QuadPart = block_size * (guint64)fsstat.f_bfree;
		}
	}

	return(TRUE);
}
