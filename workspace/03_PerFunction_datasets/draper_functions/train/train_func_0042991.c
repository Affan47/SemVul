SQLConnect (
  SQLHDBC		  hdbc,
  SQLCHAR 		* szDSN,
  SQLSMALLINT		  cbDSN,
  SQLCHAR 		* szUID,
  SQLSMALLINT		  cbUID,
  SQLCHAR 		* szAuthStr,
  SQLSMALLINT		  cbAuthStr)
{
  ENTER_HDBC (hdbc, 1,
    trace_SQLConnect (TRACE_ENTER,
    	hdbc,
	szDSN, cbDSN,
	szUID, cbUID,
	szAuthStr, cbAuthStr));

  retcode =  SQLConnect_Internal (
  	hdbc,
	szDSN, cbDSN,
	szUID, cbUID,
	szAuthStr, cbAuthStr, 'A');

  LEAVE_HDBC (hdbc, 1,
    trace_SQLConnect (TRACE_LEAVE,
    	hdbc,
	szDSN, cbDSN,
	szUID, cbUID,
	szAuthStr, cbAuthStr));
}
