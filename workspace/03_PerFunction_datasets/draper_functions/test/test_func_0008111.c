config_lookup(ares_channel channel, const char *str,
                         const char *bindch, const char *filech)
{
  char lookups[3], *l;
  const char *vqualifier p;


  l = lookups;
  p = str;
  while (*p)
    {
      if ((*p == *bindch || *p == *filech) && l < lookups + 2) {
        if (*p == *bindch) *l++ = 'b';
        else *l++ = 'f';
      }
      while (*p && !ISSPACE(*p) && (*p != ','))
        p++;
      while (*p && (ISSPACE(*p) || (*p == ',')))
        p++;
    }
  *l = '\0';
  channel->lookups = strdup(lookups);
  return (channel->lookups) ? ARES_SUCCESS : ARES_ENOMEM;
}
