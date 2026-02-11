_ds_delall_spamrecords (DSPAM_CTX * CTX, ds_diction_t diction)
{
  struct _sqlite_drv_storage *s = (struct _sqlite_drv_storage *) CTX->storage;
  ds_term_t ds_term;
  ds_cursor_t ds_c;
  buffer *query;
  char *err=NULL;
  char scratch[1024];
  char queryhead[1024];
  int writes = 0;

  if (diction->items < 1)
    return 0;

  if (s->dbh == NULL)
  {
    LOGDEBUG ("_ds_delall_spamrecords: invalid database handle (NULL)");
    return EINVAL;
  }

  query = buffer_create (NULL);
  if (query == NULL)
  {
    LOG (LOG_CRIT, ERR_MEM_ALLOC);
    return EUNKNOWN;
  }

  snprintf (queryhead, sizeof(queryhead),
            "DELETE FROM dspam_token_data"
            " WHERE token IN (");

  buffer_cat (query, queryhead);

  ds_c = ds_diction_cursor(diction);
  ds_term = ds_diction_next(ds_c);
  while (ds_term)
  {
    snprintf (scratch, sizeof (scratch), "'%" LLU_FMT_SPEC "'", ds_term->key);
    buffer_cat (query, scratch);
    ds_term = ds_diction_next(ds_c);

    if (writes > 2500 || ds_term == NULL) {
      buffer_cat (query, ")");

      if ((sqlite3_exec(s->dbh, query->data, NULL, NULL, &err))!=SQLITE_OK)
      {
        _sqlite_drv_query_error (err, query->data);
        buffer_destroy(query);
        return EFAILURE;
      }

      buffer_copy(query, queryhead);
      writes = 0;

    } else {
      writes++;
      if (ds_term)
        buffer_cat (query, ",");
    }
  }
  ds_diction_close(ds_c);

  if (writes) {
    buffer_cat (query, ")");

    if ((sqlite3_exec(s->dbh, query->data, NULL, NULL, &err))!=SQLITE_OK)
    {
      _sqlite_drv_query_error (err, query->data);
      buffer_destroy(query);
      return EFAILURE;
    }
  }

  buffer_destroy (query);
  return 0;
}
