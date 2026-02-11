config_set_groupevalnestlevel( const char *attrname, char * value, char *errorbuf, int apply ) {
  int retVal = LDAP_SUCCESS;
  long nValue = 0;
  char *endp = NULL;

  slapdFrontendConfig_t *slapdFrontendConfig = getFrontendConfig();

  if ( config_value_is_null( attrname, value, errorbuf, 0 )) {
	return LDAP_OPERATIONS_ERROR;
  }

  errno = 0;
  nValue = strtol(value, &endp, 10);

  if ( *endp != '\0' || errno == ERANGE || nValue < 0 || nValue > 5 ) {
	PR_snprintf ( errorbuf, SLAPI_DSE_RETURNTEXT_SIZE,
			  "%s: invalid value \"%s\", group eval nest level must range from 0 to 5",
			  attrname, value );
        retVal = LDAP_OPERATIONS_ERROR;
        return retVal;
  }
  if (apply) {
	CFG_LOCK_WRITE(slapdFrontendConfig);
	slapdFrontendConfig->groupevalnestlevel = nValue;
	CFG_UNLOCK_WRITE(slapdFrontendConfig);
  }
  return retVal;

}
