SQLNativeSql_Internal (SQLHDBC hdbc,
    SQLPOINTER szSqlStrIn,
    SQLINTEGER cbSqlStrIn,
    SQLPOINTER szSqlStr,
    SQLINTEGER cbSqlStrMax,
    SQLINTEGER * pcbSqlStr,
    SQLCHAR waMode)
{
  CONN (pdbc, hdbc);
  ENVR (penv, pdbc->henv);
  sqlstcode_t sqlstat = en_00000;
  SQLRETURN retcode = SQL_SUCCESS;
  HPROC hproc = SQL_NULL_HPROC;
  void * _SqlStrIn = NULL;
  void * _SqlStr = NULL;
  void * sqlStr = szSqlStr;


  if (szSqlStrIn == NULL)
    {
      sqlstat = en_S1009;
    }
  else if (cbSqlStrIn < 0 && cbSqlStrIn != SQL_NTS)
    {
      sqlstat = en_S1090;
    }

  if (sqlstat != en_00000)
    {
      PUSHSQLERR (pdbc->herr, sqlstat);
      return SQL_ERROR;
    }


  if (pdbc->state <= en_dbc_needdata)
    {
      PUSHSQLERR (pdbc->herr, en_08003);
      return SQL_ERROR;
    }

  if ((penv->unicode_driver && waMode != 'W')
      || (!penv->unicode_driver && waMode == 'W'))
    {
      if (waMode != 'W')
        {

          if ((_SqlStr = malloc(cbSqlStrMax * sizeof(SQLWCHAR) + 1)) == NULL)
	    {
              PUSHSQLERR (pdbc->herr, en_HY001);

	      return SQL_ERROR;
            }
          _SqlStrIn = dm_SQL_A2W((SQLCHAR *)szSqlStrIn, SQL_NTS);
        }
      else
        {

          if ((_SqlStr = malloc(cbSqlStrMax + 1)) == NULL)
	    {
              PUSHSQLERR (pdbc->herr, en_HY001);

	      return SQL_ERROR;
            }
          _SqlStrIn = dm_SQL_W2A((SQLWCHAR *)szSqlStrIn, SQL_NTS);
        }
      szSqlStrIn = _SqlStrIn;
      cbSqlStrIn = SQL_NTS;
      sqlStr = _SqlStr;
    }


  CALL_UDRIVER(hdbc, pdbc, retcode, hproc, penv->unicode_driver,
    en_NativeSql, (
       pdbc->dhdbc,
       szSqlStrIn,
       cbSqlStrIn,
       sqlStr,
       cbSqlStrMax,
       pcbSqlStr));

  MEM_FREE(_SqlStrIn);

  if (hproc == SQL_NULL_HPROC)
    {
      MEM_FREE(_SqlStr);
      PUSHSQLERR (pdbc->herr, en_IM001);

      return SQL_ERROR;
    }

  if (szSqlStr
      && SQL_SUCCEEDED (retcode)
      && ((penv->unicode_driver && waMode != 'W')
          || (!penv->unicode_driver && waMode == 'W')))
    {
      if (waMode != 'W')
        {

          dm_StrCopyOut2_W2A ((SQLWCHAR *) sqlStr, (SQLCHAR *) szSqlStr, cbSqlStrMax, NULL);
        }
      else
        {

          dm_StrCopyOut2_A2W ((SQLCHAR *) sqlStr, (SQLWCHAR *) szSqlStr, cbSqlStrMax, NULL);
        }
    }

  MEM_FREE(_SqlStr);

  return retcode;
}
