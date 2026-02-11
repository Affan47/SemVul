trace_SQLDriverConnectW (int trace_leave, int retcode,
  SQLHDBC		  hdbc,
  SQLHWND		  hwnd,
  SQLWCHAR 		* szConnStrIn,
  SQLSMALLINT		  cbConnStrIn,
  SQLWCHAR 		* szConnStrOut,
  SQLSMALLINT		  cbConnStrOutMax,
  SQLSMALLINT 	 	* pcbConnStrOut,
  SQLUSMALLINT		  fDriverCompletion)
{

  _trace_print_function (en_DriverConnectW, trace_leave, retcode);


  _trace_handle (SQL_HANDLE_DBC, hdbc);
  _trace_pointer (hwnd);
  _trace_connstr_w (szConnStrIn, cbConnStrIn, NULL, TRACE_INPUT);
  _trace_stringlen ("SQLSMALLINT", cbConnStrIn);
  _trace_connstr_w (szConnStrOut, cbConnStrOutMax, pcbConnStrOut,
      TRACE_OUTPUT_SUCCESS);
  _trace_stringlen ("SQLSMALLINT", cbConnStrOutMax);
  _trace_smallint_p (pcbConnStrOut, TRACE_OUTPUT_SUCCESS);
  _trace_drvcn_completion (fDriverCompletion);
}
