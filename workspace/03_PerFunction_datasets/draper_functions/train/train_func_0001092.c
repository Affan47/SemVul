_ds_del_spamrecord (DSPAM_CTX * CTX, unsigned long long token)
{
  struct _pgsql_drv_storage *s = (struct _pgsql_drv_storage *) CTX->storage;
  struct passwd *p;
  char *name;
  char query[256];
  PGresult *result;
  char tok_buf[30];

  if (s->dbh == NULL)
  {
    LOGDEBUG ("_ds_del_spamrecord: invalid database handle (NULL)");
    return EINVAL;
  }

  if (!CTX->group || CTX->flags & DSF_MERGED) {
    p = _pgsql_drv_getpwnam (CTX, CTX->username);
    name = CTX->username;
  } else {
    p = _pgsql_drv_getpwnam (CTX, CTX->group);
    name = CTX->group;
  }

  if (p == NULL)
  {
    LOGDEBUG ("_ds_del_spamrecord: unable to _pgsql_drv_getpwnam(%s)",
              name);
    return EINVAL;
  }

  snprintf (query, sizeof (query),
            "DELETE FROM dspam_token_data WHERE uid=%d AND token=%s",
            (int) p->pw_uid,
            _pgsql_drv_token_write (s->pg_token_type, token, tok_buf, sizeof(tok_buf)) );

  result = PQexec(s->dbh, query);
  if ( !result || (PQresultStatus(result) != PGRES_COMMAND_OK && PQresultStatus(result) != PGRES_NONFATAL_ERROR) )
  {
    _pgsql_drv_query_error (PQresultErrorMessage(result), query);
    if (result) PQclear(result);
    return EFAILURE;
  }
  if (result) PQclear(result);

  return 0;
}
