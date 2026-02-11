SQLFreeEnv (SQLHENV henv)
{
  GENV (genv, henv);
  int retcode = SQL_SUCCESS;

  ODBC_LOCK ();

  TRACE (trace_SQLFreeEnv (TRACE_ENTER, henv));

  retcode = SQLFreeEnv_Internal (henv);

  TRACE (trace_SQLFreeEnv (TRACE_LEAVE, henv));

  MEM_FREE (genv);


  if (--_iodbc_env_counter == 0)
    trace_stop();

  ODBC_UNLOCK ();

  return retcode;
}
