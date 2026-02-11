get_pr_path (const DatabaseInfo database, PR *pr, const char *prnum,
	    ErrorDesc *err)
{
  char *path = NULL;
  const char *category = NULL;
  char *categoryFromIndex = NULL;

  if (pr != NULL)
    {
      category = field_value (pr, CATEGORY (database));
    }
  else
    {
      categoryFromIndex = getCategoryFromIndex (database, prnum, err);
      category = categoryFromIndex;
    }

  if (category != NULL)
    {
      asprintf (&path, "%s/%s/%s", databaseDir (database), category, prnum);
      if (categoryFromIndex != NULL)
	{
	  free (categoryFromIndex);
	}
    }

  return path;
}
