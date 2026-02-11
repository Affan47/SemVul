end_login (struct credentials *pcred)
{
  char *remotehost = pcred->remotehost;
  int atype = pcred->auth_type;

  seteuid ((uid_t) 0);
  if (pcred->logged_in)
    {
      logwtmp_keep_open (ttyline, "", "");
#ifdef WITH_PAM
      pam_end_login (pcred);
#endif
    }

  free (pcred->name);
  if (pcred->passwd)
    {
      memset (pcred->passwd, 0, strlen (pcred->passwd));
      free (pcred->passwd);
    }
  free (pcred->homedir);
  free (pcred->rootdir);
  free (pcred->shell);
  if (pcred->pass)
    {
      memset (pcred->pass, 0, strlen (pcred->pass));
      free (pcred->pass);
    }
  free (pcred->message);
  memset (pcred, 0, sizeof (*pcred));
  pcred->remotehost = remotehost;
  pcred->auth_type = atype;
  pcred->logged_in = 0;
  pcred->delayed_reject = 0;
}
