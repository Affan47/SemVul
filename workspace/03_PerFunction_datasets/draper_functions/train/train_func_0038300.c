exist_field(CTABLE *table, const char *name)
{
  DB_FIELD *fp;

	if (!name || !*name)
		return FALSE;

  if (table->create)
  {
    for (fp = table->new_fields; fp; fp = fp->next)
    {
      if (!strcmp(fp->name, name))
        return TRUE;
    }

    return FALSE;
  }
  else
    return table->driver->Field.Exist(&table->conn->db, table->name, (char *)name);
}
