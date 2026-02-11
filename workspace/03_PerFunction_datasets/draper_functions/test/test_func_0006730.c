sortlist_alloc(struct apattern **sortlist, int *nsort,
                          struct apattern *pat)
{
  struct apattern *newsort;
  newsort = realloc(*sortlist, (*nsort + 1) * sizeof(struct apattern));
  if (!newsort)
    return 0;
  newsort[*nsort] = *pat;
  *sortlist = newsort;
  (*nsort)++;
  return 1;
}
