log_update_errorlogdir(char *pathname, int apply)
{

	int		rv = LDAP_SUCCESS;
	LOGFD		fp;


	if (! LOG_OPEN_APPEND(fp, pathname, loginfo.log_error_mode)) {
		char buffer[SLAPI_LOG_BUFSIZ];
		PRErrorCode prerr = PR_GetError();

		PR_snprintf(buffer, sizeof(buffer),
				"Failed to open file %s. error %d (%s). Exiting...",
				pathname, prerr, slapd_pr_strerror(prerr));
		log__error_emergency(buffer, 0, 0);
		return LDAP_UNWILLING_TO_PERFORM;
	}
	LOG_CLOSE(fp);


	if ( !apply ) {
	  return LDAP_SUCCESS;
	}


	LOG_ERROR_LOCK_WRITE ();
	if (loginfo.log_error_fdes) {
		LogFileInfo	*logp, *d_logp;

		LOG_CLOSE(loginfo.log_error_fdes);
		loginfo.log_error_fdes = 0;
		loginfo.log_error_ctime = 0;
		logp = loginfo.log_error_logchain;
		while (logp) {
			d_logp = logp;
			logp = logp->l_next;
			slapi_ch_free((void**)&d_logp);
		}
		loginfo.log_error_logchain = NULL;
		slapi_ch_free((void**)&loginfo.log_error_file);
		loginfo.log_error_file = NULL;
		loginfo.log_numof_error_logs = 1;
	}


	if ( error_log_openf (pathname, 1 )) {
		rv =  LDAP_LOCAL_ERROR;
	}

	LOG_ERROR_UNLOCK_WRITE();
	return rv;
}
