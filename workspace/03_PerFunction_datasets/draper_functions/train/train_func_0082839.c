defaultCategory (const DatabaseInfo database)
{
  if (databaseValid (database))
    {
      AdmEntry *chain = fieldDefForIndex (CATEGORY (database))->adm_contents;
      if (chain != NULL)
	{
	  char *res = xstrdup (chain->admFields[CategoryAdmKey]);
	  return res;
	}
      else
	{
	  return xstrdup ("pending");
	}
    }
  else
    {
      return NULL;
    }
}
