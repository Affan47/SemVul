_trace_sql_type_p (SQLSMALLINT *p, int output)
{
  char *ptr = "unknown SQL type";

  if (!p)
    {
      trace_emit ("\t\t%-15.15s * 0x0\n", "SQLSMALLINT");
      return;
    }

  if (!output)
    {
      trace_emit ("\t\t%-15.15s * %p\n", "SQLSMALLINT", p);
      return;
    }

  switch (*p)
    {
      _S (SQL_UNKNOWN_TYPE);
      _S (SQL_BIGINT);
      _S (SQL_BINARY);
      _S (SQL_BIT);
      _S (SQL_CHAR);
#if (ODBCVER < 0x0300)
      _S (SQL_DATE);
#else
      _S (SQL_DATETIME);
#endif
      _S (SQL_DECIMAL);
      _S (SQL_DOUBLE);
      _S (SQL_FLOAT);

#if (ODBCVER >= 0x0350)
      _S (SQL_GUID);
#endif
      _S (SQL_INTEGER);
      _S (SQL_LONGVARBINARY);
      _S (SQL_LONGVARCHAR);
      _S (SQL_NUMERIC);
      _S (SQL_REAL);
      _S (SQL_SMALLINT);
#if (ODBCVER < 0x0300)
      _S (SQL_TIME);
#else
      _S (SQL_INTERVAL);
#endif
      _S (SQL_TIMESTAMP);
      _S (SQL_TINYINT);
#if ODBCVER >= 0x0300
      _S (SQL_TYPE_DATE);
      _S (SQL_TYPE_TIME);
      _S (SQL_TYPE_TIMESTAMP);
#endif
      _S (SQL_VARBINARY);
      _S (SQL_VARCHAR);
      _S (SQL_WCHAR);
      _S (SQL_WLONGVARCHAR);
      _S (SQL_WVARCHAR);
    }

  trace_emit ("\t\t%-15.15s * %p (%s)\n", "SQLSMALLINT", p, ptr);
}
