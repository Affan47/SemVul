dl_SQLGetInfo (
   SQLHDBC               ConnectionHandle,
   SQLUSMALLINT          InfoType,
   SQLPOINTER            InfoValue,
   SQLSMALLINT           BufferLength,
   SQLSMALLINT          *StringLength)
{
      typedef SQLRETURN SQL_API ep_SQLGetInfo (
         SQLHDBC               ConnectionHandle,
         SQLUSMALLINT          InfoType,
         SQLPOINTER            InfoValue,
         SQLSMALLINT           BufferLength,
         SQLSMALLINT          *StringLength);

      ep_SQLGetInfo *fn;
      fn = (ep_SQLGetInfo *) xdlsym(h_odbc, "SQLGetInfo");
      xassert(fn != NULL);
      return (*fn)(ConnectionHandle, InfoType, InfoValue, BufferLength,
         StringLength);
}
