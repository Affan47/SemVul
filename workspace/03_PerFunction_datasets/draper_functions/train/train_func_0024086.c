get_path_from_PATH (const char *binary)
{
  char *path;
  char *pos;
  char *end;
  char *buf;
  const char *p;

  p = getenv ("PATH");
  if (p == NULL)
    return NULL;
  path = GNUNET_strdup (p);
  buf = GNUNET_malloc (strlen (path) + 20);
  pos = path;
  while (NULL != (end = strchr (pos, PATH_SEPARATOR)))
  {
    *end = '\0';
    sprintf (buf, "%s/%s", pos, binary);
    if (GNUNET_DISK_file_test (buf) == GNUNET_YES)
    {
      pos = GNUNET_strdup (pos);
      GNUNET_free (buf);
      GNUNET_free (path);
      return pos;
    }
    pos = end + 1;
  }
  sprintf (buf, "%s/%s", pos, binary);
  if (GNUNET_DISK_file_test (buf) == GNUNET_YES)
  {
    pos = GNUNET_strdup (pos);
    GNUNET_free (buf);
    GNUNET_free (path);
    return pos;
  }
  GNUNET_free (buf);
  GNUNET_free (path);
  return NULL;
}
