SQLAllocConnect_Internal (
    SQLHENV henv,
    SQLHDBC * phdbc)
{
  GENV (genv, henv);
  CONN (pdbc, NULL);

  if (phdbc == NULL)
    {
      PUSHSQLERR (genv->herr, en_S1009);
      return SQL_ERROR;
    }

  pdbc = (DBC_t *) MEM_ALLOC (sizeof (DBC_t));

  if (pdbc == NULL)
    {
      *phdbc = SQL_NULL_HDBC;

      PUSHSQLERR (genv->herr, en_S1001);
      return SQL_ERROR;
    }
  pdbc->rc = 0;


  pdbc->type = SQL_HANDLE_DBC;


  pdbc->next = (DBC_t *) genv->hdbc;
  genv->hdbc = pdbc;
#if (ODBCVER >= 0x0300)
  if (genv->odbc_ver == 0)
    genv->odbc_ver = SQL_OV_ODBC2;
  pdbc->hdesc = NULL;

  pdbc->cp_pdbc = NULL;
  pdbc->cp_in_use = FALSE;
  pdbc->cp_timeout = 0;
  pdbc->cp_expiry_time = 0;
  pdbc->cp_retry_wait = 0;
  pdbc->cp_probe = NULL;
  pdbc->cp_dsn = NULL;
  pdbc->cp_uid = NULL;
  pdbc->cp_pwd = NULL;
  pdbc->cp_connstr = NULL;
#endif
  pdbc->genv = genv;

  pdbc->henv = SQL_NULL_HENV;
  pdbc->hstmt = SQL_NULL_HSTMT;
  pdbc->herr = SQL_NULL_HERR;
  pdbc->dhdbc = SQL_NULL_HDBC;
  pdbc->state = en_dbc_allocated;
  pdbc->drvopt = NULL;
  pdbc->dbc_cip = 0;
  pdbc->err_rec = 0;


  pdbc->access_mode = SQL_MODE_DEFAULT;
  pdbc->autocommit = SQL_AUTOCOMMIT_DEFAULT;
  pdbc->current_qualifier = NULL;
  pdbc->login_timeout = 0UL;
  pdbc->odbc_cursors = SQL_CUR_DEFAULT;
  pdbc->packet_size = 0UL;
  pdbc->quiet_mode = (UDWORD) NULL;
  pdbc->txn_isolation = SQL_TXN_READ_UNCOMMITTED;
  pdbc->cb_commit = (SWORD) SQL_CB_DELETE;
  pdbc->cb_rollback = (SWORD) SQL_CB_DELETE;

  *phdbc = (SQLHDBC) pdbc;

  return SQL_SUCCESS;
}
