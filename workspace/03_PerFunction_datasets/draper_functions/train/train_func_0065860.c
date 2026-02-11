cl_file_exists(const char* filename)
{
	struct stat st;

	if (filename == NULL){
		cl_log(LOG_ERR, "%s: NULL filename",
		       __FUNCTION__);
		return FALSE;
	}

	if (lstat(filename, &st) == 0){
		return  S_ISREG(st.st_mode);
	}

	return FALSE;
}
