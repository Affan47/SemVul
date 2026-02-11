cuserid (s)
     char *s;
{
  static char name[L_cuserid];
  char buf[NSS_BUFLEN_PASSWD];
  struct passwd pwent;
  struct passwd *pwptr;

  if (__getpwuid_r (__geteuid (), &pwent, buf, sizeof (buf), &pwptr)
      || pwptr == NULL)
    {
      if (s != NULL)
	s[0] = '\0';
      return s;
    }

  if (s == NULL)
    s = name;
  s[L_cuserid - 1] = '\0';
  return strncpy (s, pwptr->pw_name, L_cuserid - 1);
}
