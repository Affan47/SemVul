setIndexDesc (DatabaseInfo database, IndexDesc new)
{
  if (databaseValid (database))
    {
      finishIndexDesc (database, new);
      database->indexDesc = new;
    }
}
