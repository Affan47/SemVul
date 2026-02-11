_libunaccept_strtopolicy(char *s)
{
  int policy = 0;

  if (strcasestr(s, "verbose")) policy |= VERBOSE;
  if (strcasestr(s, "host")) policy |= BY_HOST;

  if (strcasestr(s, "allow"))
  {
    policy |= ALLOW;
  }
  else if (strcasestr(s, "deny"))
  {
    policy |= DENY;
  }
  else if (strcasestr(s, "tarpit"))
  {
    policy |= TARPIT;
  }

  return policy;
}
