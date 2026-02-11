interndesc (hin, tan, yom)
     Wchar *hin, *tan, *yom;
{
  struct descpack *p, **pp, *next = (struct descpack *) 0;
  Wchar *s;
  int key = 0;

  for (s = hin; *s; s++)
    key += (int) *s;
  key = ((unsigned) key & HINSHIBUFINDEXMASK);
  for (pp = description + key; p = *pp; pp = &(p->next))
    {
      if (!Wscmp (p->hinshi, hin))
        {
          if (!Wscmp (p->tandesc, tan) && !Wscmp (p->yomdesc, yom))
            {
              return p;
            }
          else
            {
              *pp = next = p->next;
              freedesc (p);
              break;
            }
        }
    }
  p = (struct descpack *) malloc (sizeof (struct descpack));
  if (p)
    {
      *pp = p;
      (void) bzero (p, sizeof (struct descpack));
      p->next = next;
      p->hinshi = (Wchar *) malloc ((Wslen (hin) + 1) * sizeof (Wchar));
      if (p->hinshi)
        {
          (void) Wscpy (p->hinshi, hin);
          p->tandesc = (Wchar *) malloc ((Wslen (tan) + 1) * sizeof (Wchar));
          if (p->tandesc)
            {
              (void) Wscpy (p->tandesc, tan);
              p->yomdesc = (Wchar *) malloc ((Wslen (yom) + 1) * sizeof (Wchar));
              if (p->yomdesc)
                {
                  (void) Wscpy (p->yomdesc, yom);
                  return p;
                }
              free (p->tandesc);
            }
          free (p->hinshi);
        }
      free (p);
    }
  malloc_failed ();
  return (struct descpack *) 0;
}
