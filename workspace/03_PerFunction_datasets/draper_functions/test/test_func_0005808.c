_mysql_drv_setpwnam (DSPAM_CTX * CTX, const char *name)
{
  if (name == NULL)
    return NULL;

  char query[512];
  int query_rc = 0;
  int query_errno = 0;
  char *virtual_table, *virtual_uid, *virtual_username;
  struct _mysql_drv_storage *s = (struct _mysql_drv_storage *) CTX->storage;
  char *sql_username;

  if ((virtual_table
    = _ds_read_attribute(CTX->config->attributes, "MySQLVirtualTable"))==NULL)
  { virtual_table = "dspam_virtual_uids"; }

  if ((virtual_uid
    = _ds_read_attribute(CTX->config->attributes, "MySQLVirtualUIDField"))==NULL)
  { virtual_uid = "uid"; }

  if ((virtual_username = _ds_read_attribute(CTX->config->attributes,
    "MySQLVirtualUsernameField")) ==NULL)
  { virtual_username = "username"; }


#ifdef EXT_LOOKUP
  LOGDEBUG("_mysql_drv_setpwnam: verified_user is %d", verified_user);
  if (verified_user == 0) {
    LOGDEBUG("_mysql_drv_setpwnam: External lookup verification of %s failed: not adding user", name);
    return NULL;
  }
#endif

  sql_username = malloc (strlen(name) * 2 + 1);
  if (sql_username == NULL)
  {
    return NULL;
  }

  mysql_real_escape_string (s->dbt->dbh_write, sql_username, name,
                            strlen(name));

  snprintf (query, sizeof (query),
            "INSERT INTO %s (%s,%s) VALUES (NULL,'%s')",
            virtual_table, virtual_uid, virtual_username, sql_username);

  free (sql_username);
  sql_username = NULL;

  query_rc = MYSQL_RUN_QUERY (s->dbt->dbh_write, query);
  if (query_rc) {
    query_errno = mysql_errno (s->dbt->dbh_write);
    if (query_errno == ER_LOCK_DEADLOCK || query_errno == ER_LOCK_WAIT_TIMEOUT || query_errno == ER_LOCK_OR_ACTIVE_TRANSACTION) {

      sleep(1);
      query_rc = MYSQL_RUN_QUERY (s->dbt->dbh_write, query);
    }
  }


  if (query_rc) {
    _mysql_drv_query_error (mysql_error (s->dbt->dbh_write), query);
    LOGDEBUG ("_mysql_drv_setpwnam: unable to run query: %s", query);
    return NULL;
  }

  return _mysql_drv_getpwnam (CTX, name);

}
