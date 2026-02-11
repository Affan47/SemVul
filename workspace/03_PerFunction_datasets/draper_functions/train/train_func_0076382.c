trace_SQLGetInfo (int trace_leave, int retcode,
  SQLHDBC		  hdbc,
  SQLUSMALLINT		  fInfoType,
  SQLPOINTER		  rgbInfoValue,
  SQLSMALLINT		  cbInfoValueMax,
  SQLSMALLINT    	* pcbInfoValue)
{

  _trace_print_function (en_GetInfo, trace_leave, retcode);


  _trace_handle (SQL_HANDLE_DBC, hdbc);
  _trace_getinfo (fInfoType, rgbInfoValue, cbInfoValueMax, pcbInfoValue,
  	TRACE_OUTPUT_SUCCESS, 'A');
  _trace_smallint (cbInfoValueMax);
  _trace_smallint_p (pcbInfoValue, TRACE_OUTPUT_SUCCESS);
}
