gnats_adm_dir (const DatabaseInfo database, const char *filename)
{
  const char *ddir = databaseDir (database);
  if (ddir != NULL)
    {
      char *ptr;
      asprintf (&ptr, "%s/gnats-adm/%s", ddir, filename);
      return ptr;
    }
  else
    {
      return NULL;
    }
}
