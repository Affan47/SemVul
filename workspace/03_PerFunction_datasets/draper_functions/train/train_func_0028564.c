mail_cache_db_clean_up(struct mail_cache_db * cache_db,
    chash * exist)
{
  DB * dbp;
  int r;
  DBC * dbcp;
  DBT db_key;
  DBT db_data;

  dbp = cache_db->internal_database;

#if DB_VERSION_MAJOR == 2 && DB_VERSION_MINOR < 6
  r = dbp->cursor(dbp, NULL, &dbcp);
#else
  r = dbp->cursor(dbp, NULL, &dbcp, 0);
#endif
  if (r != 0)
    return -1;

  memset(&db_key, 0, sizeof(db_key));
  memset(&db_data, 0, sizeof(db_data));

  while (1) {
    chashdatum hash_key;
    chashdatum hash_data;

    r = dbcp->c_get(dbcp, &db_key, &db_data, DB_NEXT);
    if (r != 0)
      break;

    hash_key.data = db_key.data;
    hash_key.len = db_key.size;

    r = chash_get(exist, &hash_key, &hash_data);
    if (r < 0) {
      r = dbcp->c_del(dbcp, 0);
      if (r != 0)
        return -1;
    }
  }

  r = dbcp->c_close(dbcp);
  if (r != 0)
    return -1;

  return 0;
}
