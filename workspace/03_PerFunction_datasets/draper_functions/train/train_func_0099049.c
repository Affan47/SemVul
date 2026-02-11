_ds_get_nextuser (DSPAM_CTX * CTX)
{
  struct _mysql_drv_storage *s = (struct _mysql_drv_storage *) CTX->storage;
#ifndef VIRTUAL_USERS
  struct passwd *p;
#else
  char *virtual_table, *virtual_username;
#endif
  uid_t uid;
  char query[512];
  MYSQL_ROW row;
  int query_rc = 0;
  int query_errno = 0;

#ifdef VIRTUAL_USERS
  if ((virtual_table
    = _ds_read_attribute(CTX->config->attributes, "MySQLVirtualTable"))==NULL)
  { virtual_table = "dspam_virtual_uids"; }

  if ((virtual_username = _ds_read_attribute(CTX->config->attributes,
    "MySQLVirtualUsernameField")) ==NULL)
  { virtual_username = "username"; }
#endif

  if (s->dbt == NULL)
  {
    LOGDEBUG ("_ds_get_nextuser: invalid database handle (NULL)");
    return NULL;
  }

  if (s->iter_user == NULL)
  {
#ifdef VIRTUAL_USERS


    snprintf(query, sizeof(query), "SELECT DISTINCT %s FROM %s",
      virtual_username,
      virtual_table);
#else
    strncpy (query, "SELECT DISTINCT uid FROM dspam_stats", sizeof(query));
#endif
    query_rc = MYSQL_RUN_QUERY (s->dbt->dbh_read, query);
    if (query_rc) {
      query_errno = mysql_errno (s->dbt->dbh_read);
      if (query_errno == ER_LOCK_DEADLOCK || query_errno == ER_LOCK_WAIT_TIMEOUT || query_errno == ER_LOCK_OR_ACTIVE_TRANSACTION) {

        sleep(1);
        query_rc = MYSQL_RUN_QUERY (s->dbt->dbh_read, query);
      }
    }
    if (query_rc) {
      _mysql_drv_query_error (mysql_error (s->dbt->dbh_read), query);
      LOGDEBUG ("_ds_get_nextuser: unable to run query: %s", query);
      return NULL;
    }

    s->iter_user = mysql_use_result (s->dbt->dbh_read);
    if (s->iter_user == NULL)
      return NULL;
  }

  row = mysql_fetch_row (s->iter_user);
  if (row == NULL)
  {
    mysql_free_result (s->iter_user);
    s->iter_user = NULL;
    return NULL;
  }

  if (row[0]) {
    uid = (uid_t) atoi (row[0]);
    if (uid == INT_MAX && errno == ERANGE) {
      LOGDEBUG("_ds_get_nextuser: failed converting %s to uid", row[0]);
      return NULL;
    }
  } else {
    LOG (LOG_CRIT, "_ds_get_nextuser: detected empty or NULL uid in stats table");
    return NULL;
  }
#ifdef VIRTUAL_USERS
  strlcpy (s->u_getnextuser, row[0], sizeof (s->u_getnextuser));
#else
  p = _mysql_drv_getpwuid (CTX, uid);
  if (p == NULL)
    return NULL;

  strlcpy (s->u_getnextuser, p->pw_name, sizeof (s->u_getnextuser));
#endif

  return s->u_getnextuser;
}
