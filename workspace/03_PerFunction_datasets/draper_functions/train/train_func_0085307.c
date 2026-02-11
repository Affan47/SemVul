get_hal_device_info (const char *dev)
{
  if (!check_gudev () || !dev)
    return NULL;

  int ldev = strlen (dev);
  char buf[FILENAME_MAX + ldev + 1];
  strcpy (buf, dev);
  if (buf[0] == '/')
  {
    ldev = strrchr (buf, '/') - buf + 1;
    int tmp = readlink (dev, buf + ldev, FILENAME_MAX - 1);
    if (tmp <= 0)
      strcpy (buf, dev);
    else if (buf[ldev] == '/')
    {
      memmove (buf, buf + ldev, tmp);
      buf[tmp] = 0;
    }
    else
    {
      char *p;
      buf[ldev + tmp] = 0;
      while ((p = strstr (buf, "//")))
	memmove (p, p + 1, strlen (p));
      while ((p = strstr (buf, "/./")))
	memmove (p, p + 2, strlen (p) - 1);
      while ((p = strstr (buf, "/../")))
      {
	char *q = p;
	while (--q >= buf && *q != '/')
	  ;
	memmove (q, p + 3, strlen (p) - 2);
      }
    }
  }

  return get_gudev_property (buf, "ID_MODEL_ENC", "name");
}
