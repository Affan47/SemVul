_do_authentication (pam_handle_t *pamh,
		    pam_ldap_session_t * session,
		    const char *user, const char *password)
{
  int rc = PAM_SUCCESS;

  if (session->info == NULL)
    {
      rc = _get_user_info (session, user);
      if (rc != PAM_SUCCESS)
	return rc;
    }

  rc = _session_reopen (session);
  if (rc != PAM_SUCCESS)
    return rc;

  rc = _connect_as_user (pamh, session, password);
  _session_reopen (session);
  _connect_anonymously (session);
  return rc;
}
