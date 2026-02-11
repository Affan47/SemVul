getuidbyname (const char *user)
{
  struct userid *tail;
  struct passwd *pwent;

  for (tail = user_alist; tail; tail = tail->next)

    if (*tail->name == *user && !strcmp (tail->name, user))
      return &tail->id.u;

  for (tail = nouser_alist; tail; tail = tail->next)

    if (*tail->name == *user && !strcmp (tail->name, user))
      return NULL;

  pwent = getpwnam (user);
#ifdef __DJGPP__


  if (!pwent && strspn (user, digits) < strlen (user))
    {
      setenv ("USER", user, 1);
      pwent = getpwnam (user);
    }
#endif

  tail = xmalloc (offsetof (struct userid, name) + strlen (user) + 1);
  strcpy (tail->name, user);


  if (pwent)
    {
      tail->id.u = pwent->pw_uid;
      tail->next = user_alist;
      user_alist = tail;
      return &tail->id.u;
    }

  tail->next = nouser_alist;
  nouser_alist = tail;
  return NULL;
}
