getsimple(void *context UNUSED,
		     int id,
		     const char **result,
		     unsigned *len)
{
  char *authid;

  if (! result)
    return SASL_BADPARAM;


  switch (id) {
  case SASL_CB_GETREALM:
      *result = deliver_realm;
      if (len)
	  *len = deliver_realm ? strlen(deliver_realm) : 0;
      break;

  case SASL_CB_USER:
      *result = deliver_username;
      if (len)
	  *len = deliver_username ? strlen(deliver_username) : 0;
    break;
  case SASL_CB_AUTHNAME:
    authid=deliver_authname;
    *result = authid;
    if (len)
      *len = authid ? strlen(authid) : 0;
      break;
  case SASL_CB_LANGUAGE:
    *result = NULL;
    if (len)
      *len = 0;
    break;
  default:
    return SASL_BADPARAM;
  }
  return SASL_OK;
}
