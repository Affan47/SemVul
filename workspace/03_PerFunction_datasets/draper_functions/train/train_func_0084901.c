config_set_idletimeout( const char *attrname, char *value, char *errorbuf, int apply ) {
  int retVal = LDAP_SUCCESS;
  long nValue = 0;
  char *endp = NULL;

  slapdFrontendConfig_t *slapdFrontendConfig = getFrontendConfig();

  if ( config_value_is_null( attrname, value, errorbuf, 0 )) {
	return LDAP_OPERATIONS_ERROR;
  }

  errno = 0;
  nValue = strtol(value, &endp, 10);

  if (*endp != '\0' || errno == ERANGE || nValue < 0 ) {
        PR_snprintf ( errorbuf, SLAPI_DSE_RETURNTEXT_SIZE, "%s: invalid value \"%s\", idle timeout must range from 0 to %lld",
                      attrname, value, (long long int)LONG_MAX );
        retVal = LDAP_OPERATIONS_ERROR;
        return retVal;
  }

  if (apply) {
	CFG_LOCK_WRITE(slapdFrontendConfig);
	slapdFrontendConfig->idletimeout = nValue;

	CFG_UNLOCK_WRITE(slapdFrontendConfig);
  }
  return retVal;

}
