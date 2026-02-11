SQLEndTran_Internal (
  SQLSMALLINT		  handleType,
  SQLHANDLE		  Handle,
  SQLSMALLINT		  completionType)
{
  switch (handleType)
    {
    case SQL_HANDLE_DBC:
    case SQL_HANDLE_ENV:
      break;
    default:
      return SQL_INVALID_HANDLE;
    }

  return SQLTransact_Internal (
      handleType == SQL_HANDLE_ENV ? Handle : SQL_NULL_HENV,
      handleType == SQL_HANDLE_DBC ? Handle : SQL_NULL_HDBC,
      completionType);
}
