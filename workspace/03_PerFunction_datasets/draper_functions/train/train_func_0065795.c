ensurePathToNameExists (Loc loc, const char *name)
{
  const char *pt = FileName::path (name);
  if (*pt)
    {
      if (FileName::ensurePathExists(pt))
 	{
 	  error (loc, "cannot create directory %s", pt);
 	  fatal();
 	}
    }
}
