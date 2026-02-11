db_update_delete(void *hv, char *rli_url, char *pattern, char *errmsg)

{
  db_handle_t	*h = (db_handle_t *) hv;
  char		buf[BIGBUF];
  SQLINTEGER rli_id;
  int		rc;
  SQLRETURN	r;
  SQLLEN	rows    = 0;

  if (loglevel > 1)
    logit(LOG_DEBUG, "db_update_delete: %s %s", rli_url, PS(pattern));

  begintran(h, NULL);
  if ((rc = getid(h, rli_url, "t_rli", GLOBUS_RLS_RLI_NEXIST, &rli_id,
		  errmsg)) != GLOBUS_RLS_SUCCESS)
    goto error;
  if (pattern)
    snprintf(buf, BIGBUF, "delete from t_rlipartition where rli_id = %d and pattern = '%s'", (int) rli_id, pattern);
  else
    snprintf(buf, BIGBUF, "delete from t_rlipartition where rli_id = %d", (int) rli_id);
  r = SQLExecDirect(h->stmt, (SQLCHAR *) buf, SQL_NTS);
  if (!(SQLNODATAOK(r))) {
    odbcerr(r, SQL_HANDLE_STMT, h->stmt, errmsg);
    rc = GLOBUS_RLS_DBERROR;
    goto error;
  }
  if (pattern) {
    if (SQLOK(r)) {
      SQLRowCount(h->stmt, &rows);
    } else {
      rows = 0;
    }
    if (rows != 1) {
      snprintf(errmsg, MAXERRMSG, "%s: %s", rli_url, pattern);
      rc = GLOBUS_RLS_RLI_NEXIST;
      goto error;
    }
  } else {
    snprintf(buf, BIGBUF, "delete from t_rli where id = %d", (int) rli_id);
    r = SQLExecDirect(h->stmt, (SQLCHAR *) buf, SQL_NTS);
    if (!(SQLOK(r))) {
      odbcerr(r, SQL_HANDLE_STMT, h->stmt, errmsg);
      rc = GLOBUS_RLS_DBERROR;
      goto error;
    }
    SQLRowCount(h->stmt, &rows);
    if (rows != 1) {
      strncpy(errmsg, rli_url, MAXERRMSG);
      rc = GLOBUS_RLS_RLI_NEXIST;
      goto error;
    }
  }
  return endtran(h, SQL_COMMIT, errmsg, NULL);

 error:
  endtran(h, SQL_ROLLBACK, NULL, NULL);
  return rc;
}
