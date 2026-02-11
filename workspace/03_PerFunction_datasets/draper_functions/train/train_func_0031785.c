command_MATCH_SEQ(command_t *self, worker_t *worker, char *data,
                               apr_pool_t *ptmp) {
  char *copy;
  apr_pool_t *pool;
  COMMAND_NEED_ARG("<var-sequence>*");

  pool = module_get_config(worker->config, apr_pstrdup(ptmp, "MATCH_SEQ"));
  if (!pool) {

    apr_pool_create_unmanaged_ex(&pool, NULL, NULL);
    module_set_config(worker->config, apr_pstrdup(pool, "MATCH_SEQ"), pool);
  }

  worker->match_seq = apr_pstrdup(pool, copy);
  return APR_SUCCESS;
}
