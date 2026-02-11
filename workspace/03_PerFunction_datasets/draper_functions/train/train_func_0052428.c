trace_SQLGetDiagRecW (int trace_leave, int retcode,
  SQLSMALLINT		  HandleType,
  SQLHANDLE		  Handle,
  SQLSMALLINT		  RecNumber,
  SQLWCHAR		* SqlState,
  SQLINTEGER		* NativeErrorPtr,
  SQLWCHAR		* MessageText,
  SQLSMALLINT		  BufferLength,
  SQLSMALLINT		* TextLengthPtr)
{

  _trace_print_function (en_GetDiagRecW, trace_leave, retcode);


  _trace_handletype (HandleType);
  _trace_handle (HandleType, Handle);
  _trace_smallint (RecNumber);
  _trace_string_w (SqlState, SQL_NTS, NULL, TRACE_OUTPUT_SUCCESS);
  _trace_integer_p (NativeErrorPtr, TRACE_OUTPUT_SUCCESS);
  _trace_string_w (MessageText, BufferLength, TextLengthPtr,
      TRACE_OUTPUT_SUCCESS);
  _trace_stringlen ("SQLSMALLINT", BufferLength);
  _trace_smallint_p (TextLengthPtr, TRACE_OUTPUT_SUCCESS);
}
