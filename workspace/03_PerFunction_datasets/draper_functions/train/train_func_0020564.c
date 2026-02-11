pgsql_query(const str* query)
{
  if (result) PQclear(result);
  if ((result = PQexec(pg, query->s)) != 0) return 1;
  if (PQstatus(pg) != CONNECTION_BAD) return 0;
  PQreset(pg);
  if ((result = PQexec(pg, query->s)) != 0) return 1;
  return 0;
}
