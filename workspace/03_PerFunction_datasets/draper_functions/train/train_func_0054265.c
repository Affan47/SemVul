ParseSelector1(mp, s, slen)
MemPool mp;
char *s;
size_t slen;
{
  char *ep = s + slen;
  char *cp;
  char *last;
  CSSSelector cs;
  GList selectors;

  if ((s = ParseSpace(s, ep)) == NULL) return(NULL);

  selectors = GListCreateX(mp);

  last = s;
  cp = s;
  while (cp < ep)
  {
    if (isspace8(*cp))
    {
      if ((cs = ParseSelector2(mp, last, cp - last)) != NULL)
      {
	GListAddTail(selectors, cs);
      }

      if ((cp = ParseSpace(cp, ep)) == NULL) break;
      last = cp;
    }
    else cp++;
  }

  if (last < cp)
  {
    if ((cs = ParseSelector2(mp, last, cp - last)) != NULL)
    {
      GListAddTail(selectors, cs);
    }
  }

  if (GListGetHead(selectors) == NULL) return(NULL);

  return(selectors);
}
