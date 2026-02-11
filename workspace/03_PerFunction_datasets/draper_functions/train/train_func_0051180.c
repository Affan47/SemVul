searchdesc (hin)
     Wchar *hin;
{
  struct descpack *p, **pp;
  Wchar *s;
  int key = 0;

  for (s = hin; *s; s++)
    key += (int) *s;
  key = ((unsigned) key & HINSHIBUFINDEXMASK);
  for (pp = description + key; p = *pp; pp = &(p->next))
    {
      if (!Wscmp (p->hinshi, hin))
        {
          return p;
        }
    }
  return (struct descpack *) 0;
}
