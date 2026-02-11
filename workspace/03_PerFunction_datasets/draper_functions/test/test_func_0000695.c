error_log_openf( char *pathname, int locked)
{

	int	rv = 0;
	int	logfile_type =0;

	if (!locked) LOG_ERROR_LOCK_WRITE ();

	slapi_ch_free_string(&loginfo.log_error_file);
	loginfo.log_error_file = slapi_ch_strdup(pathname);


	slapi_ch_free_string(&loginfo.log_errorinfo_file);
	loginfo.log_errorinfo_file = slapi_ch_smprintf("%s.rotationinfo", pathname);


	logfile_type = log__error_rotationinfof(loginfo.log_errorinfo_file);

	if (log__open_errorlogfile(logfile_type, 1) != LOG_SUCCESS) {
		rv = 1;
	}

	if (!locked) LOG_ERROR_UNLOCK_WRITE();
	return rv;

}
