fsysdep_all_status_init (phold)
     pointer *phold;
{
  DIR *qdir;

  qdir = opendir ((char *) ".Status");
  if (qdir == NULL)
    {
      ulog (LOG_ERROR, "opendir (.Status): %s", strerror (errno));
      return FALSE;
    }

  *phold = (pointer) qdir;
  return TRUE;
}
