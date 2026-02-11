log_set_mode (const char *attrname, char *value, int logtype, char *errorbuf, int apply)
{
	int	v = 0;
	int	retval = LDAP_SUCCESS;
	slapdFrontendConfig_t *fe_cfg = getFrontendConfig();

	if ( NULL == value ) {
		PR_snprintf( errorbuf, SLAPI_DSE_RETURNTEXT_SIZE,
			  "%s: null value; valid values "
			  "are are of the format \"yz-yz-yz-\" where y could be 'r' or '-',"
			  " and z could be 'w' or '-'", attrname );
		return LDAP_OPERATIONS_ERROR;
	}

	if ( !apply ){
		return LDAP_SUCCESS;
	}

	v = strtol (value, NULL, 8);

	switch (logtype) {
		case SLAPD_ACCESS_LOG:
			LOG_ACCESS_LOCK_WRITE( );
			if (loginfo.log_access_file &&
				( chmod( loginfo.log_access_file, v ) != 0) ) {
				int oserr = errno;
				PR_snprintf( errorbuf, SLAPI_DSE_RETURNTEXT_SIZE,
					"%s: Failed to chmod access log file to %s: errno %d (%s)",
					attrname, value, oserr, slapd_system_strerror(oserr) );
				retval = LDAP_UNWILLING_TO_PERFORM;
			} else {
				slapi_ch_free ( (void **) &fe_cfg->accesslog_mode );
				fe_cfg->accesslog_mode = slapi_ch_strdup (value);
				loginfo.log_access_mode = v;
			}
			LOG_ACCESS_UNLOCK_WRITE();
			break;
		case SLAPD_ERROR_LOG:
			LOG_ERROR_LOCK_WRITE( );
			if (loginfo.log_error_file &&
				( chmod( loginfo.log_error_file, v ) != 0) ) {
				int oserr = errno;
				PR_snprintf( errorbuf, SLAPI_DSE_RETURNTEXT_SIZE,
					"%s: Failed to chmod error log file to %s: errno %d (%s)",
					attrname, value, oserr, slapd_system_strerror(oserr) );
				retval = LDAP_UNWILLING_TO_PERFORM;
			} else {
				slapi_ch_free ( (void **) &fe_cfg->errorlog_mode );
				fe_cfg->errorlog_mode = slapi_ch_strdup (value);
				loginfo.log_error_mode = v;
			}
			LOG_ERROR_UNLOCK_WRITE();
			break;
		case SLAPD_AUDIT_LOG:
			LOG_AUDIT_LOCK_WRITE( );
			if (loginfo.log_audit_file &&
				( chmod( loginfo.log_audit_file, v ) != 0) ) {
				int oserr = errno;
				PR_snprintf( errorbuf, SLAPI_DSE_RETURNTEXT_SIZE,
					"%s: Failed to chmod audit log file to %s: errno %d (%s)",
					attrname, value, oserr, slapd_system_strerror(oserr) );
				retval = LDAP_UNWILLING_TO_PERFORM;
			} else {
				slapi_ch_free ( (void **) &fe_cfg->auditlog_mode );
				fe_cfg->auditlog_mode = slapi_ch_strdup (value);
				loginfo.log_audit_mode = v;
			}
			LOG_AUDIT_UNLOCK_WRITE();
			break;
	}
	return retval;
}
