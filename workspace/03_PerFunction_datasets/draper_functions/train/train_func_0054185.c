_ds_delall_spamrecords (DSPAM_CTX * CTX, ds_diction_t diction)
{
  struct _mysql_drv_storage *s = (struct _mysql_drv_storage *) CTX->storage;
  ds_term_t ds_term;
  ds_cursor_t ds_c;
  buffer *query;
  char scratch[1024];
  char queryhead[1024];
  int query_rc = 0;
  int query_errno = 0;
  struct passwd *p;
  char *name;

  if (diction->items < 1)
    return 0;

  if (s->dbt->dbh_write == NULL)
  {
    LOGDEBUG ("_ds_delall_spamrecords: invalid database handle (NULL)");
    return EINVAL;
  }

  if (!CTX->group || CTX->flags & DSF_MERGED) {
    p = _mysql_drv_getpwnam (CTX, CTX->username);
    name = CTX->username;
  } else {
    p = _mysql_drv_getpwnam (CTX, CTX->group);
    name = CTX->group;
  }

  if (p == NULL)
  {
    LOGDEBUG ("_ds_delall_spamrecords: unable to _mysql_drv_getpwnam(%s)",
              name);
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
            " WHERE uid=%d AND token IN (",
            (int) p->pw_uid);


  ds_c = ds_diction_cursor(diction);
  ds_term = ds_diction_next(ds_c);
  while (ds_term) {
    scratch[0] = 0;
    buffer_copy(query, queryhead);
    while (ds_term) {
      snprintf (scratch, sizeof (scratch), "'%llu'", ds_term->key);
      buffer_cat (query, scratch);
      ds_term = ds_diction_next(ds_c);
      if((unsigned long)(query->used + 1024) > _mysql_driver_get_max_packet(s->dbt->dbh_write) || !ds_term) {
        LOGDEBUG("_ds_delall_spamrecords: Splitting query at %lu characters", query->used);
        break;
      }
      buffer_cat (query, ",");
    }
    buffer_cat (query, ")");

    query_rc = MYSQL_RUN_QUERY (s->dbt->dbh_write, query->data);
    if (query_rc) {
      query_errno = mysql_errno (s->dbt->dbh_write);
      if (query_errno == ER_LOCK_DEADLOCK || query_errno == ER_LOCK_WAIT_TIMEOUT || query_errno == ER_LOCK_OR_ACTIVE_TRANSACTION) {

        sleep(1);
        query_rc = MYSQL_RUN_QUERY (s->dbt->dbh_write, query->data);
      }
    }
    if (query_rc) {
      _mysql_drv_query_error (mysql_error (s->dbt->dbh_write), query->data);
      LOGDEBUG ("_ds_delall_spamrecords: unable to run query: %s", query->data);
      buffer_destroy(query);
      query = NULL;
      ds_diction_close(ds_c);
      return EFAILURE;
    }
  }

  ds_diction_close(ds_c);
  buffer_destroy (query);
  query = NULL;
  return 0;
}
