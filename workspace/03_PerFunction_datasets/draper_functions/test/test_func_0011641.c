_trace_stats_unique (SQLUSMALLINT type)
{
  char *ptr = "unknown option";

  switch (type)
    {
      _S (SQL_INDEX_ALL);
      _S (SQL_INDEX_UNIQUE);
    }

  trace_emit ("\t\t%-15.15s   %d (%s)\n", "SQLUSMALLINT ", (int) type, ptr);
}
