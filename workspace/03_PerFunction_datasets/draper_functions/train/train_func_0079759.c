settings_init()
{
  FILE *fp;
  char buf[513];
  char *p;

  p = getenv("HOME");
  snprintf(buf, sizeof(buf), "%s/.es.conf", p);
  fp = fopen(buf, "r");
  if (!fp) fp = fopen("/etc/es.conf", "r");
  if (!fp) return 1;
  while (fgets(buf, 512, fp))
  {
    p = buf;
    while (*p >= 32) p++;
    if (*p == 13 || *p == 10) *p = '\0';
    p = buf;
    if (!strncasecmp(buf, "env ", 4))
    {
      putenv(strdup(buf + 4));
      continue;
    }
    while (*p && *p != '=') p++;
    if (*p != '=') continue;
    *p++ = '\0';
    setting_add(buf, p);
  }
  fclose(fp);
  return 0;
}
