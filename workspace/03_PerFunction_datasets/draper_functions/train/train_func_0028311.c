_alloc_config (pam_ldap_config_t ** presult)
{
  pam_ldap_config_t *result;

  if (*presult == NULL)
    {
      *presult = (pam_ldap_config_t *) calloc (1, sizeof (*result));
      if (*presult == NULL)
	return PAM_BUF_ERR;
    }

  result = *presult;

  result->scope = LDAP_SCOPE_SUBTREE;
  result->deref = LDAP_DEREF_NEVER;
  result->configFile = NULL;
  result->host = NULL;
  result->base = NULL;
  result->port = 0;
  result->binddn = NULL;
  result->bindpw = NULL;
  result->rootbinddn = NULL;
  result->rootbindpw = NULL;
  result->ssl_on = SSL_OFF;
  result->sslpath = NULL;
  result->filter = NULL;
  result->ssd = NULL;
  result->userattr = NULL;
  result->check_userattr = 0;
  result->groupattr = NULL;
  result->groupdn = NULL;
  result->getpolicy = 0;
  result->checkhostattr = 0;
  result->checkserviceattr = 0;
#ifdef LDAP_VERSION3
  result->version = LDAP_VERSION3;
#else
  result->version = LDAP_VERSION2;
#endif
  result->timelimit = LDAP_NO_LIMIT;
  result->bind_timelimit = 10;
  result->referrals = 1;
  result->restart = 1;
  result->password_type = PASSWORD_CLEAR;
  result->min_uid = 0;
  result->max_uid = 0;
  result->tmplattr = NULL;
  result->tmpluser = NULL;
  result->tls_checkpeer = -1;
  result->tls_cacertfile = NULL;
  result->tls_cacertdir = NULL;
  result->tls_ciphers = NULL;
  result->tls_cert = NULL;
  result->tls_key = NULL;
  result->tls_randfile = NULL;
  result->logdir = NULL;
  result->sasl_mechanism = NULL;
  result->debug = 0;
  return PAM_SUCCESS;
}
