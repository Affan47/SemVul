authentificate(const char *username, const char *password, const char *service)
{
  pam_handle_t *pamh = NULL;
  int status = PAM_SUCCESS;
  int ret = 0;
  struct user_pass up;
  struct pam_conv conv;

  strncpy (up.username, username, 100);
  strncpy (up.password, password, 100);
  strncpy (up.common_name, "", 100);


  conv.conv = AuthPAM::conv;
  conv.appdata_ptr = (void *)&up;
  status = pam_start (service, up.username, &conv, &pamh);
  if (status == PAM_SUCCESS)
  {

      status = pam_authenticate(pamh, 0);
      if (status == PAM_SUCCESS)
        status = pam_acct_mgmt (pamh, 0);
      if (status == PAM_SUCCESS)
        ret = 1;


    pam_end (pamh, status);
  }

  return ret;
}
