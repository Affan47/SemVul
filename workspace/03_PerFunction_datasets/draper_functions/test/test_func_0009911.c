conv (int n, const struct pam_message **msg_array, struct pam_response **response_array, void *appdata_ptr)
{
  const struct user_pass *up = ( const struct user_pass *) appdata_ptr;
  struct pam_response *aresp;
  int i;
  int ret = PAM_SUCCESS;

  *response_array = NULL;

  if (n <= 0 || n > PAM_MAX_NUM_MSG)
    return (PAM_CONV_ERR);
  if ((aresp = (pam_response*) calloc (n, sizeof *aresp)) == NULL)
    return (PAM_BUF_ERR);


  for (i = 0; i < n; ++i)
  {
    const struct pam_message *msg = msg_array[i];
    aresp[i].resp_retcode = 0;
    aresp[i].resp = NULL;


    switch (msg->msg_style)
    {
    case PAM_PROMPT_ECHO_OFF:
      aresp[i].resp = strdup (up->password);
      if (aresp[i].resp == NULL)
        ret = PAM_CONV_ERR;
      break;

    case PAM_PROMPT_ECHO_ON:
      aresp[i].resp = strdup (up->username);
      if (aresp[i].resp == NULL)
        ret = PAM_CONV_ERR;
      break;

    case PAM_ERROR_MSG:
    case PAM_TEXT_INFO:
      break;

    default:
      ret = PAM_CONV_ERR;
      break;
    }
  }

  if (ret == PAM_SUCCESS)
    *response_array = aresp;
  return ret;
}
