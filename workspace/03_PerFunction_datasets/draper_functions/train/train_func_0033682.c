extract_members (function)
#ifdef __STDC__
     void (*function) (struct member_desc member, FILE *istream);
#else
     void (*function) ();
#endif
{
  struct mapelt *map;
  FILE *arcstream;
  char **p;

  if (!files)
    {


      scan (function, 0);
      return;
    }

  arcstream = fopen (archive, "r");
  if (!arcstream)
    fatal ("failure opening archive %s for the second time", archive);
  map = make_map (0);

  for (p = files; *p; p++)
    {
      struct mapelt *this = find_mapelt (map, *p);
      if (!this) continue;
      function (this->info, arcstream);
    }

  fclose (arcstream);
}
