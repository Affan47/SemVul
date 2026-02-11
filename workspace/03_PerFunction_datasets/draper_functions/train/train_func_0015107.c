qs_args(apr_pool_t *pool, const char *line) {
  char *last = apr_pstrdup(pool, line);
  apr_table_t* table = apr_table_make(pool, 10);
  char *val;
  while((val = apr_strtok(NULL, " ", &last))) {
    apr_table_addn(table, val, "");
  }
  return table;
}
