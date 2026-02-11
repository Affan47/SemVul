config_set_threadnumber( const char *attrname, char *value, char *errorbuf, int apply ) {
  int retVal = LDAP_SUCCESS;
  long threadnum = 0;
  char *endp = NULL;

  slapdFrontendConfig_t *slapdFrontendConfig = getFrontendConfig();

  if ( config_value_is_null( attrname, value, errorbuf, 0 )) {
	return LDAP_OPERATIONS_ERROR;
  }

  errno = 0;
  threadnum = strtol(value, &endp, 10);

  if ( *endp != '\0' || errno == ERANGE || threadnum < 1 || threadnum > 65535 ) {
	PR_snprintf ( errorbuf, SLAPI_DSE_RETURNTEXT_SIZE, "%s: invalid value \"%s\", maximum thread number must range from 1 to 65535", attrname, value );
	retVal = LDAP_OPERATIONS_ERROR;
  }

  if (apply) {
	CFG_LOCK_WRITE(slapdFrontendConfig);

	slapdFrontendConfig->threadnumber = threadnum;
	CFG_UNLOCK_WRITE(slapdFrontendConfig);
  }
  return retVal;
}
