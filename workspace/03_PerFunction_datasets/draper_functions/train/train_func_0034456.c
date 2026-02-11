GetFileAttributesEx (const gunichar2 *name, WapiGetFileExInfoLevels level, gpointer info)
{
	gchar *utf8_name;
	WapiFileAttributesData *data;

	struct stat buf, linkbuf;
	time_t create_time;
	int result;

	if (level != GetFileExInfoStandard) {
		DEBUG ("%s: info level %d not supported.", __func__,
			   level);

		SetLastError (ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	if (name == NULL) {
		DEBUG("%s: name is NULL", __func__);

		SetLastError (ERROR_INVALID_NAME);
		return(FALSE);
	}

	utf8_name = mono_unicode_to_external (name);
	if (utf8_name == NULL) {
		DEBUG ("%s: unicode conversion returned NULL", __func__);

		SetLastError (ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	result = _wapi_stat (utf8_name, &buf);
	if (result == -1 && errno == ENOENT) {

		result = _wapi_lstat (utf8_name, &buf);
	}

	if (result != 0) {
		_wapi_set_last_path_error_from_errno (NULL, utf8_name);
		g_free (utf8_name);
		return FALSE;
	}

	result = _wapi_lstat (utf8_name, &linkbuf);
	if (result != 0) {
		_wapi_set_last_path_error_from_errno (NULL, utf8_name);
		g_free (utf8_name);
		return(FALSE);
	}


	data = (WapiFileAttributesData *)info;

	if (buf.st_mtime < buf.st_ctime)
		create_time = buf.st_mtime;
	else
		create_time = buf.st_ctime;

	data->dwFileAttributes = _wapi_stat_to_file_attributes (utf8_name,
								&buf,
								&linkbuf);

	g_free (utf8_name);

	_wapi_time_t_to_filetime (create_time, &data->ftCreationTime);
	_wapi_time_t_to_filetime (buf.st_atime, &data->ftLastAccessTime);
	_wapi_time_t_to_filetime (buf.st_mtime, &data->ftLastWriteTime);

	if (data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		data->nFileSizeHigh = 0;
		data->nFileSizeLow = 0;
	}
	else {
		data->nFileSizeHigh = buf.st_size >> 32;
		data->nFileSizeLow = buf.st_size & 0xFFFFFFFF;
	}

	return TRUE;
}
