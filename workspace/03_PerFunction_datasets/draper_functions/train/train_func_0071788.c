get_dbopt(const char *dbname, HA_CREATE_INFO *create)
{
  my_dbopt_t *opt;
  uint length;
  my_bool error= 1;

  length= (uint) strlen(dbname);

  mysql_rwlock_rdlock(&LOCK_dboptions);
  if ((opt= (my_dbopt_t*) my_hash_search(&dboptions, (uchar*) dbname, length)))
  {
    create->default_table_charset= opt->charset;
    error= 0;
  }
  mysql_rwlock_unlock(&LOCK_dboptions);
  return error;
}
