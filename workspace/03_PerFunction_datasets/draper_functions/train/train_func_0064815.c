searchdesinfastakeyqueries(const char *extractkey,
                                                const Fastakeyquery
                                                  *fastakeyqueries,
                                                unsigned long numofqueries)
{
  const Fastakeyquery *leftptr, *rightptr, *midptr;
  int cmp;

  leftptr = fastakeyqueries;
  rightptr = fastakeyqueries + numofqueries - 1;
  while (leftptr <= rightptr)
  {
    midptr = leftptr + GT_DIV2((unsigned long) (rightptr-leftptr));
    cmp = strcmp(extractkey,midptr->fastakey);
    if (cmp == 0)
    {
      if (midptr > fastakeyqueries &&
          strcmp(extractkey,(midptr-1)->fastakey) == 0)
      {
        rightptr = midptr - 1;
      } else
      {
        return (unsigned long) (midptr - fastakeyqueries);
      }
    } else
    {
      if (cmp < 0)
      {
        rightptr = midptr-1;
      } else
      {
        leftptr = midptr + 1;
      }
    }
  }
  return numofqueries;
}
