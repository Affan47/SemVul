cvm_module_lookup(void)
{
  int i;


  if (!sql_query_build(query, &q)) return CVME_GENERAL | CVME_FATAL;
  if ((i = sql_auth_query(&q)) < 0) return -i;


  return (i == 1) ? 0 : CVME_PERMFAIL;
}
