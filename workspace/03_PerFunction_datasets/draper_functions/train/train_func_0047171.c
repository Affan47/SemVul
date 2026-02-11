setBinDir (DatabaseInfo database, const char *value)
{
  if (databaseValid (database))
    {
      if (database->binDirValue != NULL)
	{
	  free (database->binDirValue);
	}
      database->binDirValue = xstrdup (value);
    }
}
