SQLGetDiagRec (
  SQLSMALLINT		  HandleType,
  SQLHANDLE		  Handle,
  SQLSMALLINT		  RecNumber,
  SQLCHAR		* Sqlstate,
  SQLINTEGER		* NativeErrorPtr,
  SQLCHAR		* MessageText,
  SQLSMALLINT		  BufferLength,
  SQLSMALLINT		* TextLengthPtr)
{
  SQLRETURN retcode = SQL_SUCCESS;

  ODBC_LOCK ();

  TRACE (trace_SQLGetDiagRec (TRACE_ENTER,
  	HandleType,
	Handle,
	RecNumber,
	Sqlstate,
	NativeErrorPtr,
	MessageText, BufferLength, TextLengthPtr));

  retcode = SQLGetDiagRec_Internal (
  	HandleType,
	Handle,
	RecNumber,
	Sqlstate,
	NativeErrorPtr,
	MessageText, BufferLength, TextLengthPtr,
	'A');

  TRACE (trace_SQLGetDiagRec (TRACE_LEAVE,
  	HandleType,
	Handle,
	RecNumber,
	Sqlstate,
	NativeErrorPtr,
	MessageText, BufferLength, TextLengthPtr));

  ODBC_UNLOCK ();

  return retcode;
}
