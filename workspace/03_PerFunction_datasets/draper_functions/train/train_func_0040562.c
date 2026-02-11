set_search(ares_channel channel, const char *str)
{
  int n;
  const char *p, *q;

  if(channel->ndomains != -1) {

    for(n=0; n < channel->ndomains; n++)
      free(channel->domains[n]);
    free(channel->domains);
    channel->domains = NULL;
    channel->ndomains = -1;
  }


  n = 0;
  p = str;
  while (*p)
    {
      while (*p && !ISSPACE(*p))
        p++;
      while (ISSPACE(*p))
        p++;
      n++;
    }

  if (!n)
    {
      channel->ndomains = 0;
      return ARES_SUCCESS;
    }

  channel->domains = malloc(n * sizeof(char *));
  if (!channel->domains)
    return ARES_ENOMEM;


  n = 0;
  p = str;
  while (*p)
    {
      channel->ndomains = n;
      q = p;
      while (*q && !ISSPACE(*q))
        q++;
      channel->domains[n] = malloc(q - p + 1);
      if (!channel->domains[n])
        return ARES_ENOMEM;
      memcpy(channel->domains[n], p, q - p);
      channel->domains[n][q - p] = 0;
      p = q;
      while (ISSPACE(*p))
        p++;
      n++;
    }
  channel->ndomains = n;

  return ARES_SUCCESS;
}
