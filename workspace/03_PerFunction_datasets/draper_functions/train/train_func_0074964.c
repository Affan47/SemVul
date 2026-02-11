locate_manpage_xref (NODE *node, long int start, int dir)
{
  REFERENCE **refs;
  long position = -1;

  refs = xrefs_of_manpage (node);

  if (refs)
    {
      register int i, count;
      REFERENCE *entry;

      for (i = 0; refs[i]; i++);
      count = i;

      if (dir > 0)
        {
          for (i = 0; (entry = refs[i]); i++)
            if (entry->start > start)
              {
                position = entry->start;
                break;
              }
        }
      else
        {
          for (i = count - 1; i > -1; i--)
            {
              entry = refs[i];

              if (entry->start < start)
                {
                  position = entry->start;
                  break;
                }
            }
        }

      info_free_references (refs);
    }
  return position;
}
