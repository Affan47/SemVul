SQLAllocEnv (SQLHENV * phenv)
{
  GENV (genv, NULL);
  int retcode = SQL_SUCCESS;


  Init_iODBC();

  ODBC_LOCK ();
  retcode = SQLAllocEnv_Internal (phenv, SQL_OV_ODBC2);

  genv = (GENV_t *) *phenv;


  TRACE (trace_SQLAllocEnv (TRACE_ENTER, phenv));
  TRACE (trace_SQLAllocEnv (TRACE_LEAVE, phenv));

  ODBC_UNLOCK ();

  return retcode;
}
